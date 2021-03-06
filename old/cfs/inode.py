"""inode parsing"""

__package__ = "cfs"

import cipherinterface
import dummycipher
import longs
import memshred
import preservedio
import os

global INODE_SIZE
INODE_SIZE = 512

global UNKNOWN # unknown address or mode (all bits high)
UNKNOWN = longs.atol(longs.LONG_SIZE * "\xff")

# inode classifications

global DIRECTORY
DIRECTORY = 0

global FILE
FILE = 1

class Inode:
    """
    dull interface for inode I/O and chain traversal
    the inode index 0 is reserved
    """
    ####encryption is temporarily deactivated until we find a better solution
    def __init__(self, node, index, addr_size = longs.LONG_SIZE,
            inode_size = INODE_SIZE, cipher = dummycipher.DummyCipher(),
            new = False):
        assert not index == UNKNOWN, "index unknown"
        assert type(inode_size) in (int, long), "invalid inode_size type"
        assert addr_size > 0, "addr_size must be positive"
        assert inode_size > 3 * addr_size, "inode_size must be > 3 * addr_size"
        assert isinstance(cipher, cipherinterface.CipherInterface), "" \
               "cipher must be a cipherinterface.CipherInterface instance"
        
        self.addr_size = addr_size
        self.cipher = cipher
        self.index = index
        self.pio = preservedio.PreservedIO(node, self.index * inode_size) # wrapper for node
        self.inode_size = inode_size
        self.size_size = len(longs.ltoa(self.inode_size)) # keep this compact

        self.mode = UNKNOWN
        self.next_index = UNKNOWN
        self.prev_index = UNKNOWN
        self.size = 0 # bytes currently in-use
        
        if not new:
            self.read() # initializes node from disk

    def format(self):
        """reset the whole inode"""
        self.mode = UNKNOWN
        self.next_index = UNKNOWN
        self.prev_index = UNKNOWN
        self.size = 0

        self.write()
    
    def read(self):
        """load the inode and return the content"""
        arr = bytearray()
        
        try:
            raw = bytearray(self.pio.func(file.read, self.inode_size))

            if not raw:
                raise IOError("couldn't read node")
            
            # decipher

            #raw = self.cipher.decipher(raw)
            
            # unpack prev, mode, content, and next
            
            self.prev_index = longs.atol(raw[:self.addr_size])
            self.mode = longs.atol(raw[self.addr_size:2 * self.addr_size])
            self.size = longs.atol(raw[2 * self.addr_size:(2 * self.addr_size) + self.size_size])
            arr = bytearray(raw[(2 * self.addr_size) + self.size_size:-self.addr_size])

            if len(arr) > self.size:
                temp = arr
                arr = arr[:self.size]

                del temp
            
            self.next_index = longs.atol(raw[-self.addr_size:])

            # clean

            memshred.memshred(raw)
            
            del raw
            
        except Exception as e:
            raise e
        return arr

    def write(self, arr = None):
        """write a bytearray into the inode"""
        if not arr:
            arr = bytearray("\x00" * (self.inode_size - ((3 * self.addr_size) + self.size_size)))
        else:
            assert len(arr) <= self.inode_size - ((3 * self.addr_size) + self.size_size), "arr is too big"
            self.size = len(arr)
        
        try:
            # pack prev, mode, content, and next

            raw = bytearray("\x00" * self.inode_size)
            raw[:self.addr_size] = longs.ltopa(self.prev_index, self.addr_size)
            raw[self.addr_size:2 * self.addr_size] = longs.ltopa(self.mode, self.addr_size)
            raw[2 * self.addr_size:(2 * self.addr_size) + self.size_size] = longs.ltopa(self.size, self.size_size)
            raw[(2 * self.addr_size) + self.size_size:(2 * self.addr_size) + self.size_size + len(arr)] = arr
            raw[-self.addr_size:] = longs.ltopa(self.next_index, self.addr_size)

            # encipher

            #raw = self.cipher.encipher(raw)
            
            # write

            self.pio.func(file.write, raw)

            # clean

            memshred.memshred(raw)

            del raw
            
        except Exception as e:
            raise e

"""inode chain operations"""

__package__ = "cfs"

import inode

class InodeChain:
    """
    API for an Inode's links
    where get_vacant_inode_index must be a function
    """
    """should be a way to determine size"""
    """needs a seek method"""
    """needs to handle random extraction"""
    """needs a more logical interface"""
    def __init__(self, get_vacant_inode_index, *args, **kwargs):
        self.entry = inode.Inode(*args, **kwargs) # entry point in chain
        self._cur = None
        self.get_vacant_inode_index = get_vacant_inode_index

    def iterator(self, entry = None):
        """initialize iterator at specified or original entry point"""
        if not entry:
            entry = self.entry
        self._cur = entry
    
    def next(self):
        """return the inode and move to the next"""
        if self._cur:
            temp = self._cur

            if not self._cur.next_index == inode.UNKNOWN:
                self._cur = inode.Inode(
                    self.entry.pio.f,
                    self._cur.next_index,
                    self.entry.addr_size,
                    self.entry.inode_size
                    )
            else:
                self._cur = None
            return temp
        return None

    def prev(self):
        """return the inode and move to the previous"""
        if self._cur:
            temp = self._cur

            if not self._cur.prev_index == inode.UNKNOWN:
                self._cur = inode.Inode(
                    self.entry.pio.f,
                    self._cur.prev_index,
                    self.entry.addr_size,
                    self.entry.inode_size
                    )
            else:
                self._cur = None
            return temp
        return None

    def read(self, arr = None, b = -1, offset = 0):
        """read b bytes into the bytearray starting from the offset in the current inode"""
        """unfinished"""
        if arr == None:
            pass
        return arr

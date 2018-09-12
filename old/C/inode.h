#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
faculties for inode manipulation

an inode is a node on the filesystem tree,
and is comprised of a linked list of blocks
*/

#ifndef CFS_INODE_H
#define CFS_INODE_H

struct CFSInodeHeader {
  uint32_t parent_block; /* 0 on blocks allocated to the root inode */
  uint32_t prev_block;
  uint32_t next_block;
};

struct CFSInode {
  struct CFSInodeHeader cur_header;
  struct CFSInodeHeader entry_header;
  int fd;
  uint64_t pos;
  struct CFSProperties fs_properties;
} DEFAULT_CFSINODE;

/* close an inode */
uint8_t cfsinode_close(struct CFSInode *inode);

/* open an inode (with a dedicated file descriptor) */
struct CFSInode *cfsinode_open(int devfd, char *path);

/* read data from an inode into dest */
uint64_t cfsinode_read(char *dest, uint32_t size, uint32_t count,
  struct CFSInode *inode);

/* seek around an inode (costly) */
void cfsinode_seek(struct CFSInode *inode, uint64_t offset, uint64_t whence);

/* tell analog (constant) */
uint64_t cfsinode_tell(struct CFSInode *inode);

/* update an inode's status */
void cfsinodechain_update_status(struct CFSInode *inode,
  struct CFSStatus *status);

/* write data to an inode */
uint64_t cfsinode_write(char *src, uint32_t size, uint32_t count,
  struct CFSInode *inode);

#endif

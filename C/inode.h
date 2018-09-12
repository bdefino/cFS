#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* inode manipulation */

#ifndef CFS_INODE_H
#define CFS_INODE_H

struct CFSInodeHeader { /* full header as it appears on disk */
  struct CFSBlockHeader blockheader;
  uint8_t inodetype;
  uint64_t size;
  uint64_t block;
  char basename; /* trailing array */
};

#endif

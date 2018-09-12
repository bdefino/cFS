#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* block manipulation */

#ifndef CFS_BLOCK_H
#define CFS_BLOCK_H

struct CFSBlockHeader {
  uint64_t parent;
  uint8_t type;
};

typedef struct {
  int fd;
  struct CFSBlockHeader header;
  uint8_t newfd;
} CFSBLOCK;

#endif

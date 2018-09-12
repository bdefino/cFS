#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* block tree manipulation */

#ifndef CFS_BLOCKTREE_H
#define CFS_BLOCKTREE_H

struct CFSBlockTreeNodeHeader {
  struct CFSBlockHeader blockheader;
};

#endif

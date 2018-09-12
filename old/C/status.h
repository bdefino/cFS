#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "directory.h"
#include "type.h"

#ifndef CFS_STAT_H
#define CFS_STAT_H

struct CFSStatus { /* contains all pertinent information */
  uint32_t type;
  uint32_t head_block;
  uint16_t padding: 7;
  uint64_t size; /* in bytes */
} DEFAULT_CFSSTATUS;

/* return a path's status metadata */
struct CFSStatus *cfs_stat(struct CFSStatus *dest, int devfd, char *path);

#endif

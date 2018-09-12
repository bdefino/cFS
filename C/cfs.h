#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
cFS - an enCrypted FileSystem

note that structs are used in reference to on-disk formatting,
whereas typedefs are associated with active file descriptors
*/
/* note that encryption will be implemented later (but privacy will still be promoted) */

#ifndef CFS_H
#define CFS_H

struct CFS {
  uint64_t blocksize;
  uint64_t nblocks;
};

struct CFSHeader { /* full header as it appears on disk */
  struct CFS fs;
  uint64_t next_available_block;
  char usage; /* usage map of length .properties.nblocks / 8 */
};

typedef struct { /* makes life easier */
  int devfd;
  struct CFS fs;
} CFS;

/* close a cFS instance */
uint8_t cfs_close(CFS *fs);

/* open a cFS instance from devpath */
CFS *cfs_open(char *devpath);

#endif

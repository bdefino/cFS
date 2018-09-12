#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef CFS_API_H
#define CFS_API_H

/* directory API */

/* file API */

/* (hard) link API */

enum {
  CFS_FLAG_CLEAN_DIRTY_BYTE = 1, /* ignore data that needs to be written */
  CFS_FLAG_GHOST = 2, /* don't change (last) atime nor mtime */
  CFS_FLAG_RECOVER = 4, /* recover all remaining lost entries */
  CFS_FLAG_VERIFY_USAGE = 8 /* verify which blocks are used */
};

/* defragment the filesystem */
uint8_t cfs_defrag(int devfd, uint8_t flags);

/* check the filesystem for consistency */
uint8_t cfs_fsck(int devfd, uint8_t flags);

/* make a new filesystem */
uint8_t cfs_mkfs(int devfd, uint8_t flags);

#endif

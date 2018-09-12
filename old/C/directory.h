#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "inode.h"
#include "status.h"
#include "type.h"

#ifndef CFS_DIRECTORY_H
#define CFS_DIRECTORY_H

#ifndef cfsdirectory_close
#define cfsdirectory_close(d) cfsinodechain_close((struct CFSInodeChain *) d)
#endif

#ifndef cfsdirectory_open
#define cfsdirectory_open(d, p) ((CFSDIR *) cfsinodechain_open(d, \
  cfsinode_from_path(p)))
#endif

typedef CFSInodeChain CFSDIR;

struct CFSDirent { /* if zeroed out, ignore */
  uint32_t head_block;
  struct CFSStatus status;
  char name[256]; /* C-style string */
};

/* get an entry by name */
struct CFSDirent *cfsdirectory_get(struct CFSDirent *dest, CFSDIR *dir,
  char *name);

/* set an entry's block by name */
uint8_t cfsdirectory_link(CFSDIR *dir, char *name, uint32_t block);

/* read the next entry */
struct CFSDirent *cfsdirectory_read(struct CFSDirent *dest, CFSDIR *dir);

/* remove an entry by name */
uint8_t cfsdirectory_unlink(CFSDIR *dir, char *name);

/* update an entry by name */
uint8_t cfsdirectory_update(CFSDIR *dir, char *name, struct CFSStatus *status);

#endif

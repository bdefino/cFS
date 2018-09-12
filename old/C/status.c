#include "status.h"

DEFAULT_CFSSTATUS = (struct CFSStatus) {
  .atime = 0,
  .ctime = 0,
  .head_block = 0,
  .mtime = 0,
  .nblocks = 0,
  .padding = 0,
  .permissions = 511,
  .size = 0,
  .type = 0
};

/* return a path's status metadata */
struct CFSStatus *cfs_stat(struct CFSStatus *dest, int devfd, char *path) {
  char *basename;
  CFSDIR *dir;
  struct CFSDirent entry;
  uint8_t malloced;
  
  /* determine the dirname and basename */
  
  basename = path + strlen(path) - 1;
  malloced = dest == NULL;
  
  while (path < basename && *basename != '\\' && *basename != '/')
    basename--;
  char dirname[basename - path + 1];
  strncpy(dirname, path, basename - path);
  *(dirname + basename - path) = '\0';
  
  if ((dir = cfsdirectory_open(devfd, dirname)) == NULL)
    return NULL;
  else if ((dest == NULL && (dest = (struct CFSStatus *)
      malloc(sizeof(struct CFSStatus))) == NULL))
    cfsdirectory_close(dir); /* ignore errors */
    return NULL;
  
  if (cfsdirectory_get(&entry, basename) == NULL) {
    if (malloced)
      free(dest);
    cfsdirectory_close(dir); /* ignore errors */
    return NULL;
  }
  memcpy(dest, entry.status, sizeof(struct CFSStatus));
  cfsdirectory_close(dir); /* ignore errors */
  return dest;
}

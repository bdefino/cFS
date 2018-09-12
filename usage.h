#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* usage manipulation */

#ifndef CFS_USAGE_H
#define CFS_USAGE_H

/* return whether a block is used */
uint8_t cfsusage(CFS *fs, uint64_t block, uint8_t newfd);

/* allocate a block */
uint8_t cfsusage_alloc(CFS *fs, uint64_t block, uint8_t newfd);

/* free a block */
uint8_t cfsusage_free(CFS *fs, uint64_t block, uint8_t newfd);

/* set the usage bit for a block */
uint8_t cfsusage_set(CFS *fs, uint64_t block, uint8_t usage: 1, uint8_t newfd);

#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "inode.h"
#include "status.h"
#include "type.h"

/* cFS - an enCrypted FileSystem */

#ifndef CFS_H
#define CFS_H

struct CFSFiniteHeader {
  struct CFSProperties {
    uint32_t block_size;
    uint32_t n_blocks;
    uint16_t key_validation_chunk_size;
  } properties;
  struct CFSDynamicHeader {
    uint32_t root_block;
    uint32_t next_available_block;
    uint8_t dirty_byte;
  } dynamic_header;
} DEFAULT_CFSFINITEHEADER;

/* read the dynamic header */
struct CFSDynamicHeader cfsdynamicheader_read(int devfd);

/* read the finite header */
struct CFSHeader cfsheader_read(int devfd);

/* read the filesystem properties */
struct CFSProperties cfsproperties_read(int devfd);
#endif

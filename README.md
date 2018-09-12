# cFS - an encrypted filesystem
cFS is designed for privacy.
It doesn't store permissions, ownership, nor timestamps.
Encryption isn't currently supported, but it will be easily integrated.
## General Design
The filesystem is stored as an array of indexed blocks.
Faculties for determining the total number of blocks, their size,
and their availability are accessible via the filesystem header.
## Notes
- a block address of 0 indicates a null pointer
### Layout (see the header files for additional information)
1. header
2. blocks
#### Header
1. block size
2. block count
3. next available block index
4. block usage
#### Blocks
Each block is comprised as such:
1. parent block index
2. block type, which may be either:
  - inode
  - raw
  - tree node
3. block data
##### Block Data (Inode)
1. inode type
  - directory
  - file
2. content size (in octets)
3. block index
4. basename
##### Block Data (Raw)
1. raw data
##### Block Data (Tree Node)
1. a list of block indices referring to children

# cFS
# v2 outline
## problems
- bad seek speed
## raw outline
1. block size
2. number of blocks
3. key validation chunk size
4. root inode block index
5. next available block index
6. dirty byte
7. usage queue
8. plaintext key validation chunk
9. encrypted key validation chunk
10. blocks
## specifications
### endianness
little endian
### block index
### raw components
#### block size
uint32_t
AKA block size
#### number of blocks
uint32_t
#### key validation chunk size
uint16_t
#### root block index
uint32_t
#### next available block index
uint32_t
#### dirty byte
uint8_t
any nonzero value indicates data needs to be written to the device
#### usage queue
a packed array of bit flags representing whether each corresponding block is used
computed via
  21 + 2 * (key validation chunk size) + (number of blocks) / 8
  
  the result is then rounded up to the nearest position divisible by the block size
#### plaintext key validation chunk
#### encrypted key validation chunk
#### blocks
### API (mimics native C)

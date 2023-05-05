
#ifndef _MEM_MNG_
#define _MEM_MNG_
/* Defines the size of the memory region. */
void initMalloc( unsigned int totalSize);  

/* Corresponds to the malloc C library function */void *myMalloc(unsigned int noBytesToAllocate); 

/* Corresponds to the free C library function */
int freeMalloc( void *address);/* Dumps the contents of the block list printing in a separate line 
   the metadata associated with each contiguous memory block. */void debugBlockList();

#endif
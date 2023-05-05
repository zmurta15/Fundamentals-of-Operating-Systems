
#include "mem_mng.h"
#include <sys/mman.h>


#include <unistd.h>

typedef struct s_block *t_block;

struct s_block {
  size_t size;   // current size of block
  t_block next;  // pointer to next block
  int free; // a flag representing a free (0) or occupied (1) block; this Boolean occupies 
     // 32 bits but the compiler aligns the structure to a multiple of the word
  unsigned char data[1]; // a pointer to the data
};

#define BLOCK_SIZE sizeof(struct s_block)

t_block base;	// points to the beginning of the memory
t_block last;	// points to the last visited element of the list


/* Defines the initial size of the memory region. */
void  initMalloc( unsigned int totalSize) {
	// TODO
    base = (t_block) mmap(NULL , totalSize, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    base-> size = totalSize - BLOCK_SIZE;
    base-> free = 1;
    base->next = NULL;  
   //opcional  last = base;
}  

/* First Fit algorithm. */
t_block find_block(t_block *last , size_t size){
    t_block b=base;
    while (b && !(b->free && b->size >= size)) {
       *last = b;
        b = b->next;
    }
    return (b);
}



/* Corresponds to the malloc C library function */
void *myMalloc(unsigned int noBytesToAllocate) {
    // TODO
    t_block x = find_block(last, noBytesToAllocate);
    if(x == NULL) {
        return NULL;
    }
    //obter info de x
    if(x->size > noBytesToAllocate + BLOCK_SIZE) {
        size_t s = x->size;
        t_block n = x->next;

        //atualizar o b
        x->size = noBytesToAllocate;
        x->next = x->data + noBytesToAllocate;
        x->free = 0;

        t_block new = x->next;

        //inicializar o new 
        new->size = s - noBytesToAllocate - BLOCK_SIZE;
        new->next = n;
        new->free = 1;
    }
    else {
        x->free = 0;
    }

    return  (void*) x->data;
} 

/* Corresponds to the free C library function */
int freeMalloc( void *address) {

    // TODO

    return 0;
}


/* Dumps the contents of the block list printing in a separate line 
   the metadata associated with each contiguous memory block. */
void debugBlockList() {

    // TODO

}


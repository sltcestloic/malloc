#include <stdlib.h>
#include <pthread.h>

# define TINY_HEAP_ALLOCATION_SIZE (4 * sysconf(_SC_PAGESIZE))
# define TINY_BLOCK_SIZE (TINY_HEAP_ALLOCATION_SIZE / 128)
# define SMALL_HEAP_ALLOCATION_SIZE (32 * sysconf(_SC_PAGESIZE))
# define SMALL_BLOCK_SIZE (SMALL_HEAP_ALLOCATION_SIZE / 128)

# define HEAP_SHIFT(start) ((void *)start + sizeof(t_heap))
# define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

extern pthread_mutex_t g_malloc_mutex;

void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
#include <stdlib.h>
#include <pthread.h>

# define TINY_HEAP_ALLOCATION_SIZE (4 * sysconf(_SC_PAGESIZE))
# define TINY_BLOCK_SIZE (TINY_HEAP_ALLOCATION_SIZE / 128)
# define SMALL_HEAP_ALLOCATION_SIZE (32 * sysconf(_SC_PAGESIZE))
# define SMALL_BLOCK_SIZE (SMALL_HEAP_ALLOCATION_SIZE / 128)

# define HEAP_SHIFT(start) ((void *)start + sizeof(t_heap))
# define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

extern pthread_mutex_t 	g_malloc_mutex;
extern t_heap_chunk		*g_heap_anchor;

typedef enum	e_chunk_type {
	TINY,
	SMALL,
	LARGE
}				t_chunk_type;

typedef struct	s_heap_chunk {
	struct s_heap_chunk		*prev;
	struct s_heap_chunk		*next;
	t_chunk_type			type;
	size_t					total_size;
	size_t					free_size;
	size_t					block_count;
}				t_heap_chunk;

typedef struct	s_block {
	struct s_block	*prev;
	struct s_block	*next;
	size_t			data_size;
	t_bool			freed;
}				t_block;

void 			free(void *ptr);
void 			*malloc(size_t size);
void 			*realloc(void *ptr, size_t size);
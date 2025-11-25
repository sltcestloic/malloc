#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/resource.h>

# define TINY_HEAP_ALLOCATION_SIZE (4 * sysconf(_SC_PAGESIZE))
# define TINY_BLOCK_SIZE (TINY_HEAP_ALLOCATION_SIZE / 128)
# define SMALL_HEAP_ALLOCATION_SIZE (32 * sysconf(_SC_PAGESIZE))
# define SMALL_BLOCK_SIZE (SMALL_HEAP_ALLOCATION_SIZE / 128)

# define HEAP_SHIFT(start) ((void *)start + sizeof(t_heap_chunk))
# define BLOCK_SHIFT(start) ((void *)start + sizeof(t_block))

# define TRUE 1
# define FALSE 0

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
	int				freed;
}				t_block;

extern pthread_mutex_t 	g_malloc_mutex;
extern t_heap_chunk		*g_heap_anchor;

void 			free(void *ptr);
void 			*malloc(size_t size);
void 			*realloc(void *ptr, size_t size);

void			init_block(t_block *block, size_t size);
t_block			*fill_available_block(size_t size);
t_block			*get_last_block(t_block *block);
void			find_available_block(size_t size,
	t_heap_chunk **res_chunk, t_block **res_block);

t_heap_chunk	*get_heap_chunk_for_size(size_t size);
void			*append_empty_block(t_heap_chunk *chunk, size_t size);
t_chunk_type	get_chunk_type_from_block_size(size_t size);
t_heap_chunk	*create_heap_chunk(t_chunk_type type, size_t block_size);
size_t			get_chunk_size_from_block_size(size_t size);
void			find_pointer(t_heap_chunk **chunk_ptr, t_block **block_ptr,
	t_heap_chunk *chunk, void *ptr);
void 			remove_block_if_last(t_heap_chunk *chunk, t_block *block);
void			delete_chunk_if_empty(t_heap_chunk *chunk);

void 			ft_putstr(char const *s);
void 			ft_bzero(void *s, size_t n);
void 			*ft_memcpy(void *dest, const void *src, size_t n);
void 			*ft_memmove(void *dest, const void *src, size_t n);

void 			*handle_malloc(size_t size);
void 			handle_free(void *ptr);
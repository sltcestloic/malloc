#include "malloc.h"

static rlim_t	get_system_limit(void)
{
	struct rlimit rpl;

	if (getrlimit(RLIMIT_DATA, &rpl) < 0)
		return (-1);
	return (rpl.rlim_max);
}

t_heap_chunk *create_heap_chunk(t_chunk_type type, size_t block_size)
{
	size_t			heap_size;
	t_heap_chunk	*chunk;

	heap_size = get_chunk_size_from_block_size(block_size);
	if (heap_size > get_system_limit())
		return (NULL);
	chunk = (t_heap_chunk *)mmap(NULL, heap_size,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (chunk == MAP_FAILED)
		return (NULL);
	ft_bzero(chunk, sizeof(t_heap_chunk));
	chunk->type = type;
	chunk->total_size = heap_size;
	chunk->free_size = heap_size - sizeof(t_heap_chunk);
	return (chunk);
}
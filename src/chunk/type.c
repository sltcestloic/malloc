#include "malloc.h"

t_chunk_type	get_chunk_type_from_block_size(size_t size)
{
	if (size <= (size_t)TINY_BLOCK_SIZE)
		return (TINY);
	else if (size <= (size_t)SMALL_BLOCK_SIZE)
		return (SMALL);
	return (LARGE);
}

size_t			get_chunk_size_from_block_size(size_t size)
{
	t_chunk_type chunk_type;

	chunk_type = get_chunk_type_from_block_size(size);
	if (chunk_type == TINY)
		return ((size_t)TINY_HEAP_ALLOCATION_SIZE);
	else if (chunk_type == SMALL)
		return ((size_t)SMALL_HEAP_ALLOCATION_SIZE);
	return (size + sizeof(t_heap_chunk) + sizeof(t_block));
}

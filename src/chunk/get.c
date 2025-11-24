#include "malloc.h"

static t_heap_chunk *get_available_chunk(const t_heap_chunk *list_start,
	const t_chunk_type type, const size_t required_size)
{
	t_heap_chunk *chunk;

	chunk = (t_heap_chunk *)list_start;
	while (chunk)
	{
		if ((chunk->type == type) && (chunk->free_size >= required_size))
			return (chunk);
		chunk = chunk->next;
	}
	return (NULL);
}

t_heap_chunk *get_heap_chunk_for_size(const size_t size)
{
	t_heap_chunk	*default_heap;
	t_chunk_type	chunk_type;
	t_heap_chunk	*chunk;

	default_heap = g_heap_anchor;
	chunk_type = get_chunk_type_from_block_size(size);
	chunk = get_available_chunk(default_heap,
		chunk_type,
		size + sizeof(t_block));
	if (chunk == NULL)
	{
		if (!(chunk = create_heap_chunk(chunk_type, size)))
			return (NULL);
		chunk->next = (t_heap_chunk *)default_heap;
		if (chunk->next)
			chunk->next->prev = chunk;
		g_heap_anchor = chunk;
	}
	return (chunk);
}
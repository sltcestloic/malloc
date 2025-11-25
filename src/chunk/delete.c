#include "malloc.h"

static size_t is_last_of_preallocated(t_heap_chunk *chunk)
{
	t_heap_chunk   	*chunk_el;
	t_chunk_type	type;
	int				i;

	chunk_el = g_heap_anchor;
	type = chunk->type;
	if (type == LARGE)
		return (FALSE);
	i = 0;
	while (chunk_el)
	{
		if (chunk_el->type == type)
			i++;
		chunk_el = chunk_el->next;
	}
	return (i == 1);
}

void delete_chunk_if_empty(t_heap_chunk *chunk)
{
	if (chunk->block_count)
		return ;
	if (chunk->prev)
		chunk->prev->next = chunk->next;
	if (chunk->next)
		chunk->next->prev = chunk->prev;
	if (!is_last_of_preallocated(chunk))
	{
		if (chunk == g_heap_anchor)
			g_heap_anchor = chunk->next;
		munmap(chunk, chunk->total_size);
		ft_putstr("Chunk deleted\n");
	}
}

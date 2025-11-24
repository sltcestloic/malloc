#include "malloc.h"

void	find_available_block(size_t size, t_heap_chunk **res_chunk,
	t_block **res_block)
{
	t_heap_chunk			*chunk;
	t_block					*block;
	t_chunk_type			type;

	chunk = g_heap_anchor;
	type = get_chunk_type_from_block_size(size);
	while (chunk)
	{
		block = (t_block *)HEAP_SHIFT(chunk);
		while (chunk->type == type && block)
		{
			if (block->freed && (block->data_size >= size + sizeof(t_block)))
			{
				*res_chunk = chunk;
				*res_block = block;
				return ;
			}
			block = block->next;
		}
		chunk = chunk->next;
	}
	*res_chunk = NULL;
	*res_block = NULL;
}

t_block	*get_last_block(t_block *block)
{
	while (block->next)
		block = block->next;
	return (block);
}
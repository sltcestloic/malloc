#include "malloc.h"

static t_block	*merge_prev_block(t_heap_chunk *chunk, t_block *block)
{
	if (chunk && block && block->prev && block->prev->freed)
	{
		block->prev->next = block->next;
		if (block->next)
			block->next->prev = block->prev;
		block->prev->data_size += block->data_size + sizeof(t_block);
		chunk->block_count--;
		return (block->prev);
	}
	return (NULL);
}

static void		merge_next_block(t_heap_chunk *chunk, t_block *block)
{
	if (chunk && block && block->next && block->next->freed)
	{
		block->data_size += block->next->data_size + sizeof(t_block);
		if (block->next && block->next->next)
			block->next->next->prev = block;
		block->next = block->next->next;
		chunk->block_count--;
	}
}

t_block			*merge_block(t_heap_chunk *chunk, t_block *block)
{
	merge_next_block(chunk, block);
	return (merge_prev_block(chunk, block));
}
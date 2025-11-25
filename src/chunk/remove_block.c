#include "malloc.h"

void	remove_block_if_last(t_heap_chunk *chunk, t_block *block)
{
	if (block->freed && !block->next)
	{
		if (block->prev)
			block->prev->next = NULL;
		chunk->free_size += block->data_size + sizeof(t_block);
		chunk->block_count--;
	}
}
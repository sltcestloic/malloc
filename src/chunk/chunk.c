#include "malloc.h"
#include <stdio.h>

void *append_empty_block(t_heap_chunk *heap, size_t size)
{
	t_block	*new_block;
	t_block	*last_block;

	new_block = (t_block *)HEAP_SHIFT(heap);
	last_block = NULL;
	if (heap->block_count)
	{
		last_block = get_last_block(new_block);
		new_block =
			(t_block *)(BLOCK_SHIFT(last_block) + last_block->data_size);
	}
	init_block(new_block, size);
	if (heap->block_count)
	{
		last_block->next = new_block;
		new_block->prev = last_block;
	}
	heap->block_count++;
	heap->free_size -= (new_block->data_size + sizeof(t_block));
	return ((void *)BLOCK_SHIFT(new_block));
}
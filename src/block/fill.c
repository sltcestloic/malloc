#include "malloc.h"

static void		divide_block(t_block *block, size_t size, t_heap_chunk *chunk)
{
	t_block *free_block;

	free_block = BLOCK_SHIFT(block) + size;
	init_block(free_block, block->next - free_block);
	free_block->freed = 1;
	free_block->prev = block;
	free_block->next = block->next;
	chunk->block_count++;
	block->next = free_block;
	block->data_size = size;
	block->freed = 0;
}


t_block			*fill_available_block(size_t size)
{
	t_block			*block;
	t_heap_chunk	*chunk;

	find_available_block(size, &chunk, &block);
	if (block && chunk)
	{
		divide_block(block, size, chunk);
		return (block);
	}
	return (NULL);
}

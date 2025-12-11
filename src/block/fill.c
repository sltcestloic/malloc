#include "malloc.h"
#include <stdio.h>

static void		divide_block(t_block *block, size_t size, t_heap_chunk *chunk)
{
	t_block *free_block;

	free_block = BLOCK_SHIFT(block) + size;
	size_t new_size;
	char *chunk_end = (char *)chunk + chunk->total_size;
	if (block->next)
		new_size = (char *)block->next - (char *)free_block;
	else
		new_size = chunk_end - (char *)block;
	init_block(free_block, new_size);
	free_block->freed = TRUE;
	free_block->prev = block;
	free_block->next = block->next;	
	chunk->block_count++;
	block->next = free_block;
	block->data_size = size;
	block->freed = FALSE;
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

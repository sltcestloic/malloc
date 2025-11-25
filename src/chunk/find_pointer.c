#include "malloc.h"

void find_pointer(t_heap_chunk **chunk_ptr, t_block **block_ptr,
	t_heap_chunk *chunk, void *ptr)
{
	t_block *block;

	block = NULL;
	while (chunk)
	{
		block = (t_block *)HEAP_SHIFT(chunk);
		while (block)
		{
			if (BLOCK_SHIFT(block) == ptr)
			{
				*chunk_ptr = chunk;
				*block_ptr = block;
				return ;
			}
			block = block->next;
		}
		chunk = chunk->next;
	}
	*chunk_ptr = NULL;
	*block_ptr = NULL;
}

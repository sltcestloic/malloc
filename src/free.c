#include "malloc.h"

void handle_free(void *ptr)
{
	t_heap_chunk	*chunk;
	t_block			*block;

	chunk = g_heap_anchor;
	if (!ptr || !chunk)
		return ;
	find_pointer(&chunk, &block, chunk, ptr);
	if (block && chunk)
	{
		block->freed = TRUE;
		remove_block_if_last(chunk, block);
		delete_chunk_if_empty(chunk);
	}
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_malloc_mutex);
	handle_free(ptr);
	pthread_mutex_unlock(&g_malloc_mutex);
}

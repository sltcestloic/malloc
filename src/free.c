#include "malloc.h"

void	free(void *ptr)
{
	t_heap_chunk	*chunk;
	t_block			*block;

	pthread_mutex_lock(&g_ft_malloc_mutex);
	chunk = g_heap_anchor;
	if (!ptr || !chunk)
		return ;
	find_pointer(&chunk, &block, chunk, ptr);
	if (block && chunk)
	{
		block->freed = 1;
		remove_block_if_last(chunk, block);
		delete_chunk_if_empty(chunk);
	}
	pthread_mutex_unlock(&g_ft_malloc_mutex);
}

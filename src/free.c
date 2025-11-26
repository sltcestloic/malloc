#include "malloc.h"
#include <stdio.h>

void handle_free(void *ptr)
{
	t_heap_chunk	*chunk;
	t_block			*block;
	t_block			*ret;

	chunk = g_heap_anchor;
	if (!ptr || !chunk)
		return ;
	char buffer[100];
	snprintf(buffer, sizeof(buffer), "freeing pointer: %p\n", ptr);
	ft_putstr(buffer);
	find_pointer(&chunk, &block, chunk, ptr);
	if (block && chunk)
	{
		block->freed = TRUE;
		ft_putstr("merging blocks\n");
		ret = merge_block(chunk, block);
		block = ret ? ret : block;
		ft_putstr("removing block if last\n");
		remove_block_if_last(chunk, block);
		ft_putstr("deleting chunk if empty\n");
		delete_chunk_if_empty(chunk);
	}
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_malloc_mutex);
	ft_putstr("free called\n");
	handle_free(ptr);
	pthread_mutex_unlock(&g_malloc_mutex);
}

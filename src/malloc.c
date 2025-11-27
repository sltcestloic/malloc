#include "malloc.h"
#include <stdio.h>
#include <unistd.h>

void *handle_malloc(size_t size) {
	t_heap_chunk 	*chunk;
	t_block 		*block;
	void 			*res;
	
	size = (size + 15) & ~15;
	ft_putstr("Handling malloc, aligned size: ");
	ft_putnbr(size);
	ft_putstr("\n");
	if (size == 0)
		return NULL;
	if ((block = fill_available_block(size)))
		return BLOCK_SHIFT(block);
	ft_putstr("Finding chunk to put new block in\n");
	if (!(chunk = get_heap_chunk_for_size(size)))
		return NULL;
	ft_putstr("Appending empty block\n");
	res = append_empty_block(chunk, size);
	ft_putstr("Appended empty block done\n");
	return res;
}

void *malloc(size_t size) {
	void *ptr = NULL;
	pthread_mutex_lock(&g_malloc_mutex);
	ft_putstr("Malloc called with size: ");
	ft_putnbr(size);
	ft_putstr("\n");
	ptr = handle_malloc(size);
	ft_putstr("Malloc handled\n");
	pthread_mutex_unlock(&g_malloc_mutex);
	ft_putstr("Malloc complete\n");
	return ptr;
}
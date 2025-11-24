#include "malloc.h"
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void *handle_malloc(size_t size) {
	t_heap_chunk 	*chunk;
	t_block 		*block;
	void 			*res;
	
	ft_putstr("Handling malloc\n");
	if ((block = fill_available_block(size))) {
		return BLOCK_SHIFT(block);
	}
	ft_putstr("Finding heap chunk\n");
	if (!(chunk = get_heap_chunk_for_size(size))) {
		return NULL;
	}
	ft_putstr("Appending empty block\n");
	res = append_empty_block(chunk, size);
	return res;
}

void *malloc(size_t size) {
	void *ptr = NULL;
	pthread_mutex_lock(&g_malloc_mutex);
	size = (size + 15) & ~15;
	if (size == 0) {
		pthread_mutex_unlock(&g_malloc_mutex);
		return NULL;
	}
	ptr = handle_malloc(size);
	pthread_mutex_unlock(&g_malloc_mutex);
	ft_putstr("Malloc complete\n");
	return ptr;
}
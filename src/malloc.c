#include "malloc.h"
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

void *handle_malloc(size_t size) {
	t_heap_chunk 	*chunk;
	t_block 		*block;
	
}

void *malloc(size_t size) {
	void *ptr = NULL;
	pthread_mutex_lock(&g_malloc_mutex);
	size = (size + 15) & ~15;
	if (size == 0) {
		pthread_mutex_unlock(&g_malloc_mutex);
		return NULL;
	}
	
	pthread_mutex_unlock(&g_malloc_mutex);
	return ptr;
}
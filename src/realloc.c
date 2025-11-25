#include "malloc.h"

void *handle_realloc(void *ptr, size_t size)
{
	t_heap_chunk	*chunk;
	t_block			*block;
	void			*new_ptr;

	if (!ptr)
		return (handle_malloc(size));
	else if (size == 0)
	{
		handle_free(ptr);
		return (NULL);
	}
	chunk = g_heap_anchor;
	find_pointer(&chunk, &block, chunk, ptr);
	if (!chunk || !block)
		return (NULL);
	else if (size == block->data_size)
		return (ptr);
	new_ptr = handle_malloc(size);
	ft_memmove(new_ptr, ptr, block->data_size > size ? size : block->data_size);
	handle_free(ptr);
	return (new_ptr);
}

void *realloc(void *ptr, size_t size)
{
	void *ret;

	pthread_mutex_lock(&g_malloc_mutex);
	ret = handle_realloc(ptr, size);
	pthread_mutex_unlock(&g_malloc_mutex);
	return (ret);
}

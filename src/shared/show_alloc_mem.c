#include "malloc.h"
#include <stdio.h>

void show_alloc_mem()
{
	t_heap_chunk	*chunk = g_heap_anchor;
	pthread_mutex_lock(&g_malloc_mutex);
	while (chunk)
	{
		char *label;
		if (chunk->type == TINY)
			label = "TINY";
		else if (chunk->type == SMALL)
			label = "SMALL";
		else
			label = "LARGE";
		ft_putstr(label);
		ft_putstr(" : ");
		char buffer[100];
		snprintf(buffer, sizeof(buffer), "%p\n", (void *)chunk);
		ft_putstr(buffer);
		t_block *block = (t_block *)HEAP_SHIFT(chunk);
		while (block)
		{
			char buffer[100];
			snprintf(buffer, sizeof(buffer), "%p", (void *)block);
			ft_putstr(buffer);
			snprintf(buffer, sizeof(buffer), " - %p", (void *)((char *)block + sizeof(t_block) + block->data_size));
			ft_putstr(buffer);
			ft_putstr(" : ");
			ft_putnbr(block->data_size);
			ft_putstr(" bytes\n");
			block = block->next;
		}
		chunk = chunk->next;
	}
	pthread_mutex_unlock(&g_malloc_mutex);
}
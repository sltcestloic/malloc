#include "malloc.h"
#include <stdio.h>

void init_block(t_block *block, size_t size)
{
	ft_putstr("Initializing block ");
	char buf[256];
	snprintf(buf, sizeof(buf),
		"%p",
		(void*)block);
	ft_putstr(buf);
	ft_putstr(" with size ");
	ft_putnbr(size);
	ft_putstr("\n");
	block->prev = NULL;
	block->next = NULL;
	block->data_size = size;
	ft_putstr("Block data size set to ");
	ft_putnbr(block->data_size);
	ft_putstr("\n");
	block->freed = FALSE;
}

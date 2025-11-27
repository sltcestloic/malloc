#include "malloc.h"

void	ft_putstr(char const *s)
{
	int i;

	if (!getenv("MALLOC_DEBUG"))
		return ;
	i = 0;
	while (s[i])
		i++;
	write(2, s, i);
}
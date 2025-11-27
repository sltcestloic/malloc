#include "malloc.h"

void ft_putnbr(int n) __attribute__((weak));


int	main(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		ft_putnbr(addr[0]);
		i++;
	}
	return (0);
}

#include "malloc.h"

void	ft_putnbr(int nb)
{
	long	nbr;

	if (!getenv("MALLOC_DEBUG"))
		return ;
	nbr = nb;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr > 9)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	else
	{
 		char c = '0' + nbr;
        write(2, &c, 1);	
	}
}
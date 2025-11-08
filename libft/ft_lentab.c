#include "libft.h"

int ft_lentab(char **tab)
{
	int len = 0;

	while (tab[len])
		len++;
	return (len);
}
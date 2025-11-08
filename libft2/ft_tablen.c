#include "libft.h"

int ft_tablen(char **tab)
{
	int len = 0;

	while (tab[len])
		len++;
	return (len);
}
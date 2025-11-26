#include "libft.h"

void	free_split(char **tab, size_t i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
}

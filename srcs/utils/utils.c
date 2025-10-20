#include "miniRT.h"

void free_tab(char **tab)
{
	int i = 0;

	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
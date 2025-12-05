#include "../GNL/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int		fd;
	unsigned long long		*tab[178];
	int		line;
	int		line2;
	unsigned long long	fresh;
	int		i_str;
	unsigned long long		start;
	unsigned long long end;
	char	*str;

	ac++;
	fd = open(av[1], O_RDONLY);
	line = 0;
	fresh = 0;
	while (line < 177)
	{
		i_str = 0;
		start = 0;
		end = 0;
		tab[line] = malloc(sizeof(unsigned long long) * 2);
		str = get_next_line(fd);
		while (str[i_str] != '-')
			start = start * 10 + str[i_str++] - '0';
		i_str++;
		while (str[i_str] != '\n')
			end = end * 10 + str[i_str++] - '0';
		tab[line][0] = start;
		tab[line][1] = end;
		free(str);
		line++;
	}
	tab[line] = NULL;
	line = 0;
	while (line < 177)
	{
		line2 = line+1;
		while (line2 < 177)
		{
			if (tab[line][0] >= tab[line2][0] && tab[line][1] <= tab[line2][1])
				tab[line][0] = tab[line2][1]+1;
			if (tab[line][1] >= tab[line2][0] && tab[line][1] <= tab[line2][1])
				tab[line][1] = tab[line2][0]-1;
			line2++;
		}
		if (tab[line][0] <= tab[line][1])
			fresh+=(tab[line][1]-tab[line][0]+1);
		line++;
	}
	printf("fresh = %lld\n", fresh);
	return (0);
}

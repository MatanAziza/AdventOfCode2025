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
	int		fresh;
	unsigned long long		nbr;
	int		i_str;
	unsigned long long		start;
	unsigned long long end;
	char	*str;

	ac++;
	fd = open(av[1], O_RDONLY);
	line = 0;
	fresh = 0;
	nbr = 0;
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
	while (1)
	{
		i_str = 0;
		nbr = 0;
		str = get_next_line(fd);
		if (str[0] == 'x')
			break ;
		line = 0;
		while (str[i_str] != '\n')
			nbr = nbr * 10 + str[i_str++] - '0';
		while (line < 177)
		{
			if (tab[line][0] <= nbr && nbr <= tab[line][1])
			{
				fresh++;
				break ;
			}
			line++;
		}
	}
	printf("Number of fresh ingredients in the ranges : %d\n", fresh);
	return (0);
}

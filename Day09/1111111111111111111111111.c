#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../GNL/get_next_line_________________________.h"

int	main(int ac, char **av)
{
	int	fd = open(av[ac-1], O_RDONLY);
	long long *tab[496];
	int i = 0;
	char *str;
	int j;
	while (i < 496)
	{
		str = get_next_line(fd);
		j = 0;
		tab[i] = malloc(sizeof(long long)*2);
		tab[i][0] = 0;
		tab[i][1] = 0;
		while (str[j] != ',')
			tab[i][0] = tab[i][0]*10+str[j++]-'0';
		j++;
		while (str[j] != '\n')
			tab[i][1] = tab[i][1]*10+str[j++]-'0';
		free(str);
		printf("%lld, %lld\n", tab[i][0], tab[i][1]);
		i++;
	}
	i = 0;
	long long abs_lon;
	long long abs_larg;
	long long area = 0;
	while (i< 495)
	{
		j = i+1;
		while (j < 496)
		{
			abs_lon = (tab[i][0]-tab[j][0] >= 0) ? tab[i][0] - tab[j][0]+1 : tab[j][0] - tab[i][0]+1;
			abs_larg = (tab[i][1]-tab[j][1] >= 0) ? tab[i][1] - tab[j][1]+1 : tab[j][1] - tab[i][1]+1;
			if (abs_larg*abs_lon >= area)
				area = abs_lon*abs_larg;
			j++;
		}
		i++;
	}
	printf("%lld\n", area);
	return (0);
}

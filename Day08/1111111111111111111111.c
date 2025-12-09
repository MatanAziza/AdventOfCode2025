/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1111111111111111111111.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maziza <matan.aziza@learner.42.tech>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:36:22 by maziza            #+#    #+#             */
/*   Updated: 2025/12/09 16:56:40 by maziza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../GNL/get_next_line_________________________.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#ifndef ABS
# define ABS(x) (x > 0) ? x : -x;
#endif

void	ft_swap(float **couples, int j, int i_max)
{
	float temp, x, y;
	temp = couples[i_max][0];
	couples[i_max][0] = couples[j][0];
	couples[j][0] = temp;
	x = couples[i_max][1];
	couples[i_max][1] = couples[j][1];
	couples[j][1] = x;
	y = couples[i_max][2];
	couples[i_max][2] = couples[j][2];
	couples[j][2] = y;
}

int	main(int ac, char **av)
{
	int fd = open(av[ac-1], O_RDONLY);
	int	*tab[1000];
	int	i = 0;
	int	j;
	int	x;
	int	y;
	int	z;
	char *str;
	while (i < 1000)
	{
		j = 0;
		x = 0;
		y = 0;
		z = 0;
		str = get_next_line(fd);
		while (str[j] != ','){
			x = x*10 + str[j]-'0';
			j++;
		}
		j++;
		while (str[j] != ','){
			y = y*10 + str[j]-'0';
			j++;
		}
		j++;
		while (str[j] != '\n'){
			z = z*10 + str[j]-'0';
			j++;
		}
		tab[i] = malloc(sizeof(int)*3);
		tab[i][0] = x;
		tab[i][1] = y;
		tab[i][2] = z;
		free(str);
		i++;
	}
	float	**couples;
	couples = malloc(sizeof(float *)*499500);
	i = 0;
	int i_couples = 0;
	while (i < 999)
	{
		j = i + 1;
		while (j < 1000)
		{
			couples[i_couples] = malloc(sizeof(float)*3);
			x = ABS((tab[i][0] - tab[j][0]));
			y = ABS((tab[i][1] - tab[j][1]));
			z = ABS((tab[i][2] - tab[j][2]));
			printf("%d, %d, %d, %d\n",x, y, z, i_couples);
			couples[i_couples][0] = sqrt(((long)x*(long)x + (long)y*(long)y + (long)z*(long)z));
			printf("%f, %d, %d\n", couples[i_couples][0], i, j);
			couples[i_couples][1] = i;
			couples[i_couples][2] = j;
			j++;
			i_couples++;
		}
		i++;
	}
	i = 499500;
	int	i_max;
	while (i)
	{
		i_max = 0;
		j = 0;
		while (j < i)
		{
			if (couples[j][0] > couples[i_max][0])
				i_max = j;
			j++;
		}
		ft_swap(couples, j-1, i_max);
		i--;
	}
	int	*range;
	range = malloc(sizeof(int)*1000);
	i = 0;
	while (i < 1000)
		range[i++] = 0;
	i = 0;
	j = 0;
	while (i < 1000)
	{
		printf("%f\n", couples[i][0]);
		if (range[(int)couples[i][1]] == 0)
			range[(int)couples[i][1]] = 1;
		if (range[(int)couples[i][2]] == 0)
			range[(int)couples[i][2]] = 1;
		i++;
	}
	i = 0;
	while (i < 1000)
	{
		if (range[i] == 1)
			j++;
		i++;
	}
	printf("Members of the network : %d\n", j);
	close(fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maziza <matan.aziza@learner.42.tech>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:59:55 by maziza            #+#    #+#             */
/*   Updated: 2025/12/04 11:01:29 by maziza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../GNL/get_next_line_________________________.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
	char *tab[136];
	int	i = 0;
	int	j;
	int	count = 0;
	int	accessible = 0;
	int	fd = open(av[ac-1], O_RDONLY);
	while (i < 135)
		tab[i++] = get_next_line(fd);
	tab[i] = NULL;
	i = 0;
	while (i < 135)
	{
		j = 0;
		while (j < 135)
		{
			count = 0;
			if (j > 0 && i > 0)
			{
				if (tab[i-1][j-1] == '@')
					count++;
			}
			if (i > 0)
			{
				if (tab[i-1][j] == '@')
					count++;
			}
			if (i > 0 && j < 134)
			{

				if (tab[i-1][j+1] == '@')
					count++;
			}
			if (j > 0)
			{

				if (tab[i][j-1] == '@')
					count++;
			}
			if (j < 134)
			{

				if (tab[i][j+1] == '@')
					count++;
			}
			if (j > 0 && i < 134)
			{

				if (tab[i+1][j-1] == '@')
					count++;
			}
			if (i < 134)
			{

				if (tab[i+1][j] == '@')
					count++;
			}
			if (j < 134 && i < 134)
			{

				if (tab[i+1][j+1] == '@')
					count++;
			}
			if (count < 4 && tab[i][j] == '@')
				accessible++;
			j++;
		}
		i++;
	}
	printf("Number of rolls accessible : %d\n", accessible);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1111111111111111111.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maziza <matan.aziza@learner.42.tech>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 08:50:25 by maziza            #+#    #+#             */
/*   Updated: 2025/12/07 09:03:10 by maziza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../GNL/get_next_line_________________________.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int fd = open(av[ac-1], O_RDONLY);
	int	i = 0;
	int	j;
	char *tab[143];
	int	count = 0;
	while (i < 143)
		tab[i++] = get_next_line(fd);
	tab[i] = NULL;
	i = 1;
	while (i < 142)
	{
		j = 0;
		while (j < 140)
		{
			if ((tab[i-1][j] == '.' || tab[i-1][j] == '|') && tab[i][j] != '/')
				tab[i][j] = '|';
			if (tab[i][j] == '/' && tab[i-1][j] == '|')
			{
				count++;
				tab[i][j-1] = '|';
				tab[i][j+1] = '|';
			}
			j++;
		}
		i++;
	}
	i = 0;
	printf("Nombre de zones où le tachyon peut atterrir : %i\n", count);
	return (0);
}

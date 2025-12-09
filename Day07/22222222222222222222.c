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
	int					fd;
	int					i;
	long long int		**tab;
	char				*str;
	int					j;
	unsigned long long	count;

	fd = open(av[ac - 1], O_RDONLY);
	i = 0;
	tab = malloc(sizeof(long long int *) * (142));
	while (i < 142)
	{
		j = 0;
		str = get_next_line(fd);
		tab[i] = malloc(sizeof(long long int) * (142));
		while (j < 141)
		{
			tab[i][j] = (long long int)str[j] - '0';
			j++;
		}
		tab[i][j] = 0;
		i++;
		free(str);
	}
	i = 1;
	while (i < 142)
	{
		j = 0;
		while (j < 141)
		{
			if (tab[i - 1][j] == -2)
				tab[i][j]++;
			if (tab[i - 1][j] >= 0 && tab[i][j] != -1 && tab[i - 1][j] != 0)
				tab[i][j] += tab[i - 1][j];
			if (tab[i][j] == -1 && tab[i - 1][j] > tab[i][j])
			{
				tab[i][j - 1] += (tab[i - 1][j]);
				tab[i][j + 1] += (tab[i - 1][j]);
			}
			j++;
		}
		i++;
	}
	j = 0;
	count = 0;
	while (j < 141)
	{
		count += tab[141][j];
		j++;
	}
	printf("Possible differents ways the tachyon can take : %lld\n", count);
	return (0);
}

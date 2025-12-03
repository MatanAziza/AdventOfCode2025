/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maziza <matan.aziza@learner.42.tech>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:35:09 by maziza            #+#    #+#             */
/*   Updated: 2025/12/04 00:53:47 by maziza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../GNL/get_next_line.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>

int	ft_power(int x, int y)
{
	if (y == 0)
		return (1);
	if (y < 0)
		return (0);
	return (x * ft_power(x, y - 1));
}

int	main(int ac, char **av)
{
	int					i;
	char				*turn;
	int					fd;
	unsigned long long	final_nb;
	unsigned long long	nb;
	unsigned long long	dizaine;
	unsigned long long	units;

	fd = open(av[ac - 1], O_RDONLY);
	while (1)
	{
		final_nb = 0;
		while (1)
		{
			nb = 0;
			turn = get_next_line(fd);
			if (turn[0] == 'x')
				break ;
			i = 0;
			dizaine = i;
			while (i < 99)
			{
				if (turn[i] > turn[dizaine])
					dizaine = i;
				i++;
			}
			nb += (turn[dizaine] - '0') * 10;
			i = dizaine + 1;
			units = i;
			while (i < 100)
			{
				if (turn[i] > turn[units])
					units = i;
				i++;
			}
			nb += turn[units] - '0';
			final_nb += nb;
		}
		if (turn[0] == 'x')
			break ;
	}
	printf("Set of 2 batteries to turn on with the highet joltage : %lld\n", final_nb);
	return (0);
}

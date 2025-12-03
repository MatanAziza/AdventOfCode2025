/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maziza <matan.aziza@learner.42.tech>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:35:09 by maziza            #+#    #+#             */
/*   Updated: 2025/12/02 14:36:47 by maziza           ###   ########.fr       */
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
	unsigned long long	value;
	unsigned long long	nb_start;
	unsigned long long	nb_end;
	int					len_nb;
	unsigned long long	nb_copy;
	char				*turn;
	int					fd;

	value = 0;
	fd = open(av[ac - 1], O_RDONLY);
	while (1)
	{
		i = 0;
		nb_start = 0;
		nb_end = 0;
		turn = get_next_line(fd);
		if (turn[0] == 'x')
			break ;
		while (turn[i] != '-')
			nb_start = nb_start * 10 + turn[i++] - '0';
		i++;
		while (turn[i] != '\n')
			nb_end = nb_end * 10 + turn[i++] - '0';
		while (nb_start <= nb_end)
		{
			len_nb = 0;
			nb_copy = nb_start;
			while (nb_copy != 0)
			{
				len_nb++;
				nb_copy /= 10;
			}
			if (len_nb % 2 == 0)
			{
				if (nb_start / ft_power(10, len_nb / 2) == nb_start
					% ft_power(10, len_nb / 2))
					value += nb_start;
			}
			nb_start++;
		}
	}
	printf("final value = %lld\n", value);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maziza <matan.aziza@learner.42.tech>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:35:09 by maziza            #+#    #+#             */
/*   Updated: 2025/12/04 00:54:04 by maziza           ###   ########.fr       */
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
	unsigned long long	centbillion;
	unsigned long long	dixbillion;
	unsigned long long	billion;
	unsigned long long	centmillion;
	unsigned long long	dixmillion;
	unsigned long long	million;
	unsigned long long	centm;
	unsigned long long	dixm;
	unsigned long long	mille;
	unsigned long long	cent;
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
			centbillion = 0;
			while (i < 89)
			{
				if (turn[i] > turn[centbillion])
					centbillion = i;
				i++;
			}
			nb += (turn[centbillion] - '0') * (unsigned long long)100000000000;
			i = centbillion + 1;
			dixbillion = i;
			while (i < 90)
			{
				if (turn[i] > turn[dixbillion])
					dixbillion = i;
				i++;
			}
			nb += (turn[dixbillion] - '0') * (unsigned long long)10000000000;
			i = dixbillion + 1;
			billion = i;
			while (i < 91)
			{
				if (turn[i] > turn[billion])
					billion = i;
				i++;
			}
			nb += (turn[billion] - '0') * (unsigned long long)1000000000;
			i = billion + 1;
			centmillion = i;
			while (i < 92)
			{
				if (turn[i] > turn[centmillion])
					centmillion = i;
				i++;
			}
			nb += (turn[centmillion] - '0') * 100000000;
			i = centmillion + 1;
			dixmillion = i;
			while (i < 93)
			{
				if (turn[i] > turn[dixmillion])
					dixmillion = i;
				i++;
			}
			nb += (turn[dixmillion] - '0') * 10000000;
			i = dixmillion + 1;
			million = i;
			while (i < 94)
			{
				if (turn[i] > turn[million])
					million = i;
				i++;
			}
			nb += (turn[million] - '0') * 1000000;
			i = million + 1;
			centm = i;
			while (i < 95)
			{
				if (turn[i] > turn[centm])
					centm = i;
				i++;
			}
			nb += (turn[centm] - '0') * 100000;
			i = centm + 1;
			dixm = i;
			while (i < 96)
			{
				if (turn[i] > turn[dixm])
					dixm = i;
				i++;
			}
			nb += (turn[dixm] - '0') * 10000;
			i = dixm + 1;
			mille = i;
			while (i < 97)
			{
				if (turn[i] > turn[mille])
					mille = i;
				i++;
			}
			nb += (turn[mille] - '0') * 1000;
			i = mille + 1;
			cent = i;
			while (i < 98)
			{
				if (turn[i] > turn[cent])
					cent = i;
				i++;
			}
			nb += (turn[cent] - '0') * 100;
			i = cent + 1;
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
	printf("Set of 12 batteries to turn on with the highet joltage : %lld\n", final_nb);
	return (0);
}

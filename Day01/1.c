/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maziza <matan.aziza@learner.42.tech>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:47:24 by maziza            #+#    #+#             */
/*   Updated: 2025/12/04 00:50:07 by maziza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../GNL/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	ft_sign(int nb)
{
	if (nb >= 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	int		zero_count;
	int		i;
	int		pos_tab;
	int		fd;
	char	*turn;
	int		side_rotation;
	int		nb_rotation;

	zero_count = 0;
	i = 0;
	pos_tab = 50;
	fd = open(av[ac - 1], O_RDONLY);
	while (1)
	{
		i = 1;
		nb_rotation = 0;
		turn = get_next_line(fd);
		if (turn[0] == 'x')
			break ;
		if (turn[0] == 'L')
			side_rotation = -1;
		else
			side_rotation = 1;
		while (turn[i] != '\n' && turn[i] != '\0')
			nb_rotation = nb_rotation * 10 + turn[i++] - '0';
		pos_tab = (pos_tab + (side_rotation * nb_rotation)) % 100;
		if (pos_tab == 0)
			zero_count++;
	}
	printf("Number of times the safe dial stopped on \"0\" stops : %d\n", zero_count);
	return (0);
}

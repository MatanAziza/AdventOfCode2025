/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maziza <matan.aziza@learner.42.tech>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 09:59:55 by maziza            #+#    #+#             */
/*   Updated: 2025/12/04 136:00:04 by maziza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../GNL/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while ((char)str[i])
		i++;
	return (i);
}
char	*ft_strdupp(const char *s)
{
	size_t	len;
	size_t	i;
	char	*out;

	if (s == NULL)
		return (NULL);
	len = ft_strlen((char *)s);
	out = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		out[i] = s[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

int	main(int ac, char **av)
{
	char *tab[136];
	int	i = 0;
	int	j;
	int	count = 0;
	int	accessible = 0;
	int	total = 0;
	int	fd = open(av[ac-1], O_RDONLY);
	while (i < 135)
		tab[i++] = get_next_line(fd);
	tab[i] = NULL;
	i = 0;
	while (i < 135)
		printf("%s", tab[i++]);
	while (1)
	{
		i = 0;
		accessible = 0;
		while (i < 135)
		{
			j = 0;
			while (j < 135)
			{
				count = 0;
				if (j > 0 && i > 0)
				{
					if (tab[i-1][j-1] == '@' || tab[i-1][j-1] == 'x')
						count++;
				}
				if (i > 0)
				{
					if (tab[i-1][j] == '@' || tab[i-1][j] == 'x')
						count++;
				}
				if (i > 0 && j < 134)
				{
					if (tab[i-1][j+1] == '@' || tab[i-1][j+1] == 'x')
						count++;
				}
				if (j > 0)
				{
					if (tab[i][j-1] == '@' || tab[i][j-1] == 'x')
						count++;
				}
				if (j < 134)
				{
					if (tab[i][j+1] == '@' || tab[i][j+1] == 'x')
						count++;
				}
				if (j > 0 && i < 134)
				{
					if (tab[i+1][j-1] == '@' || tab[i+1][j-1] == 'x')
						count++;
				}
				if (i < 134)
				{
					if (tab[i+1][j] == '@' || tab[i+1][j] == 'x')
						count++;
				}
				if (j < 134 && i < 134)
				{
					if (tab[i+1][j+1] == '@' || tab[i+1][j+1] == 'x')
						count++;
				}
				if (count < 4 && tab[i][j] == '@')
				{
					accessible++;
					tab[i][j] = 'x';
				}
				j++;
			}
			printf("%s",tab[i]);
			i++;
		}
		i = 0;
		while (i < 135)
		{
			j = 0;
			while (j < 135)
			{
				if (tab[i][j] == 'x')
					tab[i][j] = '.';
				j++;
			}
			i++;
		}
		printf("Nb of rolls removed : %d\n", total);
		if (accessible == 0)
			break;
		total += accessible;
	}
	return (0);
}

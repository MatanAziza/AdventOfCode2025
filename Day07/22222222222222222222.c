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

int     main(int ac, char **av)
{
    int fd = open(av[ac-1], O_RDONLY);
    int     i = 0;
    unsigned long long int **tab;
    char *str;
    int     j;
    tab = malloc(sizeof(unsigned long long int *)*(142));
    while (i < 142)
    {
            j = 0;
            str = get_next_line(fd);
            printf("%s", str);
            tab[i] = malloc(sizeof(unsigned long long int)*(142));
            while (j < 141)
            {
                    tab[i][j] = (unsigned long long int)str[j];
                    j++;
            }
            tab[i][j] = 0;
            i++;
            free(str);
    }
    printf("\n");
    i = 1;
    while (i < 142)
    {
        j = 0;
        while (j < 141)
        {
            if (tab[i-1][j] == 'S')
                tab[i][j]++;
            if (tab[i-1][j] != '-' && tab[i-1][j] != 'S' && tab[i][j] != '-' && tab[i-1][j] != '0')
                tab[i][j] += (tab[i-1][j]-'0');
            if (tab[i][j] == '-' && tab[i-1][j] > tab[i][j])
            {
                tab[i][j-1]+=(tab[i-1][j]-'0');
                tab[i][j+1]+=(tab[i-1][j]-'0');
            }
            j++;
        }
        i++;
    }
    unsigned long long count = 0;
	j = 0;
    while (j < 141)
    {
        count += ((int)tab[141][j]);
        j++;
    }
    count -= (141*'0');
    printf("count = %lld\n", count);
    return (0);
}

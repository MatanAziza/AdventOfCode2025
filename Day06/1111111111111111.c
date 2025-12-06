#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <gmp.h>
#include "../GNL/get_next_line.h"


static int      ft_nb_words(const char *s, char c)
{
        int     i;
        int     count;

        i = 1;
        count = 0;
        if (!s[0])
                return (0);
        if (s[0] != c)
                count++;
        while ((char)s[i])
        {
                if ((char)s[i - 1] == c && (char)s[i] != c)
                        count++;
                i++;
        }
        return (count);
}

static int      *ft_indexes(const char *s, char c, int nb_words)
{
        int     *indexes_words;
        int     i;
        int     j;

        j = 0;
        indexes_words = malloc(sizeof(int) * (nb_words + 1));
        if (!indexes_words)
                return (NULL);
        if (!s[0])
        {
                indexes_words[0] = -1;
                return (indexes_words);
        }
        i = 1;
        if ((char)s[0] != c)
                indexes_words[j++] = 0;
        while ((char)s[i])
        {
                if ((char)s[i - 1] == c && (char)s[i] != c)
                        indexes_words[j++] = i;
                i++;
        }
        indexes_words[j] = -1;
        return (indexes_words);
}

static char     *ft_fill_tab(const char *s, char c, int index)
{
        int             i;
        int             len;
        char    *word;

        i = 0;
        len = 0;
        while (s[index + len] != c && s[index + len] != '\0')
                len++;
        word = malloc(len + 1);
        if (!word)
                return (NULL);
        while (s[index + i] != c && s[index + i] != '\0')
        {
                word[i] = s[index + i];
                i++;
        }
        word[i] = '\0';
        return (word);
}

void    *ft_freess(int *indexes, char **tab)
{
        int     i;

        i = 0;
        if (tab)
        {
                while (tab[i])
                {
                        free(tab[i]);
                        i++;
                }
                free(tab);
        }
        if (indexes)
                free(indexes);
        return (NULL);
}

char    **ft_split(char const *s, char c)
{
        int             nb_words;
        int             *indexes_words;
        int             i;
        char    **tab;

        nb_words = ft_nb_words(s, c);
        indexes_words = ft_indexes(s, c, nb_words);
        tab = malloc(sizeof(char *) * (nb_words + 1));
        if (!tab || !indexes_words)
                return (ft_freess(indexes_words, tab));
        i = 0;
        while (indexes_words[i] != -1)
        {
                tab[i] = ft_fill_tab(s, c, indexes_words[i]);
                if (!tab[i])
                        return (ft_freess(indexes_words, tab));
                i++;
        }
        free(indexes_words);
        tab[i] = NULL;
        return (tab);
}
int main(int ac, char **av)
{   int fd = open(av[1], O_RDONLY);    char *line1 = get_next_line(fd);
    char *line2 = get_next_line(fd);
    char *line3 = get_next_line(fd);
    char *line4 = get_next_line(fd);
    char *mult  = get_next_line(fd);
    char **tab1 = ft_split(line1, ' ');
    char **tab2 = ft_split(line2, ' ');
    char **tab3 = ft_split(line3, ' ');
    char **tab4 = ft_split(line4, ' ');
    char **tabmult = ft_split(mult, ' ');

    mpz_t final_nb;
    mpz_init(final_nb);
    mpz_set_ui(final_nb, 0);

    int i = 0;
    while (tabmult[i] && i < 1000)
    {
        mpz_t nb1, nb2, nb3, nb4, tmp;
        mpz_init(nb1); mpz_init(nb2); mpz_init(nb3); mpz_init(nb4); mpz_init(tmp);

        mpz_set_str(nb1, tab1[i], 10);
        mpz_set_str(nb2, tab2[i], 10);
        mpz_set_str(nb3, tab3[i], 10);
        mpz_set_str(nb4, tab4[i], 10);

        if (tabmult[i][0] == '+') {
            mpz_add(tmp, nb1, nb2);
            mpz_add(tmp, tmp, nb3);
            mpz_add(tmp, tmp, nb4);
        } else {
            mpz_mul(tmp, nb1, nb2);
            mpz_mul(tmp, tmp, nb3);
            mpz_mul(tmp, tmp, nb4);
        }

        mpz_add(final_nb, final_nb, tmp);

        mpz_clear(nb1); mpz_clear(nb2); mpz_clear(nb3); mpz_clear(nb4); mpz_clear(tmp);
        i++;
    }

    gmp_printf("The sums and products following left-right direction gave : %Zd\n", final_nb);
	ac++;
    // Libération mémoire
    mpz_clear(final_nb);
    close(fd);
    return 0;
}


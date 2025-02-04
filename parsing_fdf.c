/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:59:09 by aykrifa           #+#    #+#             */
/*   Updated: 2025/02/04 12:32:40 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "lib.h"
//#include "libft/get_next_line.h"
#include "Libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "fdf.h"

int	count_words(const char *s, char *c)
{
	int	i;
	int	words;
	int	k;

	i = 0;
	words = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c[0] || s[i] == c[1])
			k = 0;
		else if (k == 0)
		{
			words++;
			k = 1;
		}
		i++;
	}
	return (words);
}

t_coordinate	fill_coordinate(t_list *lst)
{
	t_coordinate	coordinate;
	int		i;
	int		j;
	int		k;

	coordinate.map = ft_calloc(ft_lstsize(lst), sizeof(int *));
	coordinate.maxy = ft_lstsize(lst);
	coordinate.maxx = count_words(lst->s, " \n");
	i = 0;
	while (lst)
	{
		(coordinate.map)[i] = malloc(count_words(lst->s, " \n") * sizeof(int));
		j = 0;
		k = 0;
		while (j < count_words(lst->s, " \n"))
		{
			(coordinate.map)[i][j] = ft_atoi(&(lst->s)[k]);
			while (ft_isdigit((lst->s)[k]))
				k++;
			while ((lst->s)[k] == ' ' || (lst->s)[k] == '\n')
				k++;
			j++;
		}
		i++;
		lst = lst->next;
	}
	return (coordinate);
}

void	liberator_int_tab(int **tab, int line)
{
	int	i;

	i = 0;
	while (i < line)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	print_int_tab(int **tab, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("%2d ", tab[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

t_coordinate	dup_map(char *file)
{
	t_coordinate	coordinate;
	char	*s;
	int		fd;
	t_list	*lst;

	lst = NULL;
	fd = open(file, O_RDONLY);
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		ft_lstadd_back(&lst, ft_lstnew(s));
	}
	coordinate = fill_coordinate(lst);
	print_int_tab(coordinate.map, ft_lstsize(lst), coordinate.maxx);
//	liberator_int_tab(coordinate.map, ft_lstsize(lst));
	close(fd);
	ft_lstclear(&lst, free);
	return (coordinate);
}

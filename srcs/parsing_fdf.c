/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:06:26 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/21 09:28:59 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include <stdio.h>

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

static int	isbase(char c, char *base)
{
	int	i;

	i = 0;
	while (i < base[i])
	{
		if (c == base[i])
			return (i);
	i++;
	}
	return (-1);
}

void	calloc_rows_set_max(t_list *lst, t_data *fdf)
{
	fdf->shpere = 0;
	fdf->coordinate.maxy = ft_lstsize(lst);
	if (!fdf->coordinate.maxy)
		ft_exit(fdf, lst, FAILURE);
	fdf->coordinate.maxx = count_words(lst->s, " \n");
	if (!fdf->coordinate.maxx)
		ft_exit(fdf, lst, FAILURE);
	fdf->coordinate.map = ft_calloc(fdf->coordinate.maxy, sizeof(t_z *));
	if (!fdf->coordinate.map)
		ft_exit(fdf, lst, FAILURE);
}

void	fill_coordinate(t_list *lst, t_data *fdf, int i, int j)
{
	int		k;
	t_list	*current;

	calloc_rows_set_max(lst, fdf);
	current = lst;
	while (current)
	{
		(fdf->coordinate.map)[i] = malloc(fdf->coordinate.maxx * sizeof(t_z));
		if (!fdf->coordinate.map)
			ft_exit(fdf, lst, FAILURE);
		j = 0;
		k = 0;
		while (j < count_words(lst->s, " \n"))
		{
			(fdf->coordinate.map)[i][j].x = j;
			(fdf->coordinate.map)[i][j].y = i;
			(fdf->coordinate.map)[i][j].z = ft_atoi(&(current->s)[k]);
			while (ft_isdigit((current->s)[k]))
				k++;
			if ((!i && !j) || (fdf->coordinate.map[i][j].z > fdf->coordinate.maxz))
				fdf->coordinate.maxz = fdf->coordinate.map[i][j].z;
			if ((!i && !j) || (fdf->coordinate.map[i][j].z < fdf->coordinate.minz))
				fdf->coordinate.minz = fdf->coordinate.map[i][j].z;
			if (current->s[k] == ',')
			{
				k += 3;
				fdf->coordinate.map[i][j].color = ft_atoi_base(&current->s[k], "0123456789ABCDEF");
				fdf->coordinate.map[i][j].colorh = ft_atoi_base(&current->s[k], "0123456789abcdef");
				if (fdf->coordinate.map[i][j].colorh > fdf->coordinate.map[i][j].color)
					fdf->coordinate.map[i][j].color = fdf->coordinate.map[i][j].colorh;
			}
			else
				fdf->coordinate.map[i][j].color = 0x810202;
			while (isbase(current->s[k], "0123456789ABCDEFabcdef") != -1)
				k++;
			while ((current->s)[k] == ' ' || (current->s)[k] == '\n')
				k++;
			j++;
		}
		i++;
		current = current->next;
	}
}

void	liberator_int_tab(t_z **tab, int line)
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

void	print_int_tab(t_z **tab, int y, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("%2f ", tab[i][j].z);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	dup_map(char *file, t_data *fdf)
{
	char	*s;
	int		fd;
	t_list	*lst;
	t_list	*node;

	lst = NULL;
	fd = open(file, O_RDONLY);
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		node = ft_lstnew(s);
		if (!node)
		{
			free(s);
			break ;
		}
		ft_lstadd_back(&lst, node);
	}
	fill_coordinate(lst, fdf, 0, 0);
	close(fd);
	ft_lstclear(&lst, free);
}

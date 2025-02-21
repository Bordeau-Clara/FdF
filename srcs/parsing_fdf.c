/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:06:26 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/21 18:01:02 by cbordeau         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include <stdio.h>

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

int	color(t_data *fdf, char *nb, int i, int j)
{
	fdf->coordinate.map[i][j].color = ft_atoi_base(nb, "0123456789ABCDEF");
	fdf->coordinate.map[i][j].colorh = ft_atoi_base(nb, "0123456789abcdef");
	if (fdf->coordinate.map[i][j].colorh > fdf->coordinate.map[i][j].color)
		fdf->coordinate.map[i][j].color = fdf->coordinate.map[i][j].colorh;
	return (3);
}

int	skip_caract_set_color(t_data *fdf, char *s, int i, int j)
{
	int	k;

	k = 0;
	if ((!i && !j) || (fdf->coordinate.map[i][j].z > fdf->coordinate.maxz))
		fdf->coordinate.maxz = fdf->coordinate.map[i][j].z;
	if ((!i && !j) || (fdf->coordinate.map[i][j].z < fdf->coordinate.minz))
		fdf->coordinate.minz = fdf->coordinate.map[i][j].z;
	while (ft_isdigit(s[k]) || s[k] == '-')
		k++;
	if (s[k] == ',')
		k += color(fdf, &s[k + 3], i, j);
	else
		fdf->coordinate.map[i][j].color = 0x810202;
	while (isbase(s[k], "0123456789ABCDEFabcdef") != -1)
		k++;
	while (s[k] == ' ' || s[k] == '\n')
		k++;
	return (k);
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
		while (j < fdf->coordinate.maxx)
		{
			(fdf->coordinate.map)[i][j].x = j;
			(fdf->coordinate.map)[i][j].y = i;
			(fdf->coordinate.map)[i][j].z = ft_atoi(&(current->s)[k]);
			k += skip_caract_set_color(fdf, &current->s[k], i, j);
			j++;
		}
		i++;
		current = current->next;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fdf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:06:26 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/22 16:19:49 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include <stdio.h>

void	calloc_rows_set_max(t_list *lst, t_data *fdf)
{
	fdf->shpere = 0;
	fdf->maxy = ft_lstsize(lst);
	if (!fdf->maxy)
		ft_exit(fdf, lst, FAILURE);
	fdf->maxx = count_words(lst->s, " \n");
	if (!fdf->maxx)
		ft_exit(fdf, lst, FAILURE);
	fdf->coordinate = ft_calloc(fdf->maxy, sizeof(t_coordinate *));
	if (!fdf->coordinate)
		ft_exit(fdf, lst, FAILURE);
}

int	color(t_data *fdf, char *nb, int i, int j)
{
	int	color_hex_up;
	int	color_hex_low;

	color_hex_up = ft_atoi_base(nb, "0123456789ABCDEF");
	color_hex_low = ft_atoi_base(nb, "0123456789abcdef");
	if (color_hex_up > color_hex_low)
			fdf->coordinate[i][j].color = color_hex_up;
	else
			fdf->coordinate[i][j].color = color_hex_low;
	return (3);
}

int	skip_caract_set_color(t_data *fdf, char *s, int i, int j)
{
	int	k;

	k = 0;
	if ((!i && !j) || (fdf->coordinate[i][j].z > fdf->maxz))
		fdf->maxz = fdf->coordinate[i][j].z;
	if ((!i && !j) || (fdf->coordinate[i][j].z < fdf->minz))
		fdf->minz = fdf->coordinate[i][j].z;
	while (ft_isdigit(s[k]) || s[k] == '-')
		k++;
	if (s[k] == ',')
		k += color(fdf, &s[k + 3], i, j);
	else
		fdf->coordinate[i][j].color = 0x810202;
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
		fdf->coordinate[i] = malloc(fdf->maxx * sizeof(t_coordinate));
		if (!fdf->coordinate)
			ft_exit(fdf, lst, FAILURE);
		j = 0;
		k = 0;
		while (j < fdf->maxx)
		{
			fdf->coordinate[i][j].x = j;
			fdf->coordinate[i][j].y = i;
			fdf->coordinate[i][j].z = ft_atoi(&(current->s)[k]);
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
	while (TRUE)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:16:00 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/20 18:46:42 by cbordeau         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_coordinate	dup_fdf(t_coordinate coordinate)
{
	t_coordinate	save;
	int				i;
	int				j;

	i = -1;
	save.maxx = coordinate.maxx;
	save.maxy = coordinate.maxy;
	save.maxz = coordinate.maxz;
	save.minz = coordinate.minz;
	save.map = malloc(save.maxy * sizeof(t_z *));
	if (!save.map)
		return (save);
	while (++i < coordinate.maxy)
	{
		j = -1;
		save.map[i] = malloc(save.maxx * sizeof(t_z));
		if (!save.map[i])
			return (liberator_int_tab(save.map, i), save);
		while (++j < coordinate.maxx)
		{
			save.map[i][j].z = coordinate.map[i][j].z;
			save.map[i][j].color = coordinate.map[i][j].color;
		}
	}
	return (save);
}

void	restore(t_data *fdf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	fdf->mode = 0;
	fdf->coordinate.maxx = fdf->save.maxx;
	fdf->coordinate.maxy = fdf->save.maxy;
	fdf->coordinate.maxz = fdf->save.maxz;
	fdf->coordinate.minz = fdf->save.minz;
	while (i < fdf->save.maxy)
	{
		j = 0;
		while (j < fdf->save.maxx)
		{
			fdf->coordinate.map[i][j].z = fdf->save.map[i][j].z;
			fdf->coordinate.map[i][j].color = fdf->save.map[i][j].color;
			j++;
		}
		i++;
	}
}

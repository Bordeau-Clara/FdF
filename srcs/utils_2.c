/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:16:00 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/21 11:36:55 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_coordinate	dup_fdf(t_coordinate coordinate, int i, int j)
{
	t_coordinate	save;

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
			save.map[i][j].x = coordinate.map[i][j].x;
			save.map[i][j].y = coordinate.map[i][j].y;
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
			fdf->coordinate.map[i][j].x = fdf->save.map[i][j].x;
			fdf->coordinate.map[i][j].y = fdf->save.map[i][j].y;
			fdf->coordinate.map[i][j].z = fdf->save.map[i][j].z;
			fdf->coordinate.map[i][j].color = fdf->save.map[i][j].color;
			j++;
		}
		i++;
	}
}

void	move_z(t_data *fdf, int mode)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->coordinate.maxy)
	{
		j = 0;
		while (j < fdf->coordinate.maxx)
		{
			if (fdf->coordinate.map[i][j].z != fdf->coordinate.minz
				&& mode == 1)
				fdf->coordinate.map[i][j].z += 1;
			if (fdf->coordinate.map[i][j].z > fdf->coordinate.minz + 1
				&& mode == 0)
				fdf->coordinate.map[i][j].z -= 1;
			j++;
		}
		i++;
	}
	if (mode == 1 && fdf->coordinate.minz + 1 != fdf->coordinate.maxz)
		fdf->coordinate.maxz += 1;
	if (mode == 0 && fdf->coordinate.minz + 1 != fdf->coordinate.maxz)
		fdf->coordinate.maxz -= 1;
}

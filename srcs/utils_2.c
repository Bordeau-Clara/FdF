/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:16:00 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/22 08:42:05 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	dup_fdf(t_data *fdf, int i, int j)
{
	fdf->reset.maxx = fdf->maxx;
	fdf->reset.maxy = fdf->maxy;
	fdf->reset.maxz = fdf->maxz;
	fdf->reset.minz = fdf->minz;
	fdf->save = malloc(fdf->maxy * sizeof(t_coordinate *));
	if (!fdf->save)
		return ;
	while (++i < fdf->maxy)
	{
		j = -1;
		fdf->save[i] = malloc(fdf->maxx * sizeof(t_coordinate));
		if (!fdf->save[i])
			return (liberator_int_tab(fdf->save, i));
		while (++j < fdf->maxx)
		{
			fdf->save[i][j].x = fdf->coordinate[i][j].x;
			fdf->save[i][j].y = fdf->coordinate[i][j].y;
			fdf->save[i][j].z = fdf->coordinate[i][j].z;
			fdf->save[i][j].color = fdf->coordinate[i][j].color;
		}
	}
}

void	restore(t_data *fdf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	fdf->mode = 0;
	fdf->offset = set_offset(*fdf);
	fdf->maxx = fdf->reset.maxx;
	fdf->maxy = fdf->reset.maxy;
	fdf->maxz = fdf->reset.maxz;
	fdf->minz = fdf->reset.minz;
	while (i < fdf->reset.maxy)
	{
		j = 0;
		while (j < fdf->reset.maxx)
		{
			fdf->coordinate[i][j].x = fdf->save[i][j].x;
			fdf->coordinate[i][j].y = fdf->save[i][j].y;
			fdf->coordinate[i][j].z = fdf->save[i][j].z;
			fdf->coordinate[i][j].color = fdf->save[i][j].color;
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
	while (i < fdf->maxy)
	{
		j = 0;
		while (j < fdf->maxx)
		{
			if (fdf->coordinate[i][j].z != fdf->minz
				&& mode == 1)
				fdf->coordinate[i][j].z += 1;
			if (fdf->coordinate[i][j].z > fdf->minz + 1
				&& mode == 0)
				fdf->coordinate[i][j].z -= 1;
			j++;
		}
		i++;
	}
	if (mode == 1 && fdf->minz + 1 != fdf->maxz)
		fdf->maxz += 1;
	if (mode == 0 && fdf->minz + 1 != fdf->maxz)
		fdf->maxz -= 1;
}

void	z_to_zero(t_data *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->maxy)
	{
		j = 0;
		while (j < fdf->maxx)
		{
			if (fdf->coordinate[i][j].z > fdf->minz)
				fdf->coordinate[i][j].z = fdf->minz + 1;
			j++;
		}
		i++;
	}
	fdf->maxz = fdf->minz + 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:56:42 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/11 12:23:13 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	find_color(t_data fdf, int base, int final, int i, int j)
{
	t_rgb	colora;
	t_rgb	colorb;
	t_rgb	color;
	float	ratio;

	if (fdf.coordinate.map[i][j].z <= fdf.coordinate.minz)
		return (base);
	if (fdf.coordinate.map[i][j].z >= fdf.coordinate.maxz)
		return (final);
	ratio = (float)(fdf.coordinate.map[i][j].z - fdf.coordinate.minz) / (fdf.coordinate.maxz - fdf.coordinate.minz);
	colora.r = (base >> 16) & 0xFF;
	colora.g = (base >> 8) & 0xFF;
	colora.b = base & 0xFF;
	colorb.r = (final >> 16) & 0xFF;
	colorb.g = (final >> 8) & 0xFF;
	colorb.b = final & 0xFF;
	color.r = colora.r + (colorb.r - colora.r) * ratio;
	color.g = colora.g + (colorb.g - colora.g) * ratio;
	color.b = colora.b + (colorb.b - colora.b) * ratio;
	return ((color.r << 16) | (color.g << 8) | color.b);
}

/*void	change_base_color(t_data *fdf, int base, int up)
{
	int i;
	int j;

	i = 0;
	while (i < fdf->coordinate.maxy)
	{
		j = 0;
		while (j < fdf->coordinate.maxx)
		{
			if (fdf->coordinate.map[i][j].color != 0xFFFFFF)
				fdf->coordinate.map[i][j].color = base;
			else
				fdf->coordinate.map[i][j].color = up; 
			j++;
		}
		i++;
	}
}*/

void	change_color(t_data *fdf, int base, int final)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->coordinate.maxy)
	{
		j = 0;
		while (j < fdf->coordinate.maxx)
		{
			if (fdf->coordinate.map[i][j].z == fdf->coordinate.minz)
				fdf->coordinate.map[i][j].color = base;
			else
				fdf->coordinate.map[i][j].color = find_color(*fdf, base, final, i, j);
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
			if (fdf->coordinate.map[i][j].z != fdf->coordinate.minz && mode == 1)
			{
				fdf->coordinate.map[i][j].z += 1;
			}
			if (fdf->coordinate.map[i][j].z > fdf->coordinate.minz + 1 && mode == 0)
			{
				fdf->coordinate.map[i][j].z -= 1;
			}
			j++;
		}
		i++;
	}
	if (mode == 1 && fdf->coordinate.minz + 1 != fdf->coordinate.maxz)
		fdf->coordinate.maxz += 1;
	if (mode == 0 && fdf->coordinate.minz + 1 != fdf->coordinate.maxz)
		fdf->coordinate.maxz -= 1;
}

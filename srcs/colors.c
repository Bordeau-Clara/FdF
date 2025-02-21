/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:56:42 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/21 18:14:07 by cbordeau         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	interpolate_color(int color1, int color2, float t)
{
	t_rgb	colora;
	t_rgb	colorb;
	t_rgb	color;

	colora.r = (color1 >> 16) & 0xFF;
	colora.g = (color1 >> 8) & 0xFF;
	colora.b = color1 & 0xFF;
	colorb.r = (color2 >> 16) & 0xFF;
	colorb.g = (color2 >> 8) & 0xFF;
	colorb.b = color2 & 0xFF;
	color.r = (int)(colora.r + t *(colorb.r - colora.r));
	color.g = (int)(colora.g + t *(colorb.g - colora.g));
	color.b = (int)(colora.b + t *(colorb.b - colora.b));
	return ((color.r << 16) | (color.g << 8) | color.b);
}

int	find_color(t_data fdf, int base, int final, t_offset p)
{
	t_rgb	colora;
	t_rgb	colorb;
	t_rgb	color;
	float	ratio;

	if (fdf.coordinate.map[p.x][p.y].z <= fdf.coordinate.minz)
		return (base);
	if (fdf.coordinate.map[p.x][p.y].z >= fdf.coordinate.maxz)
		return (final);
	ratio = (float)(fdf.coordinate.map[p.x][p.y].z - fdf.coordinate.minz) / \
		(fdf.coordinate.maxz - fdf.coordinate.minz);
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
	t_offset	p;

	p.x = 0;
	while (p.x < fdf->coordinate.maxy)
	{
		p.y = 0;
		while (p.y < fdf->coordinate.maxx)
		{
			if (fdf->coordinate.map[p.x][p.y].z == fdf->coordinate.minz)
				fdf->coordinate.map[p.x][p.y].color = base;
			else
				fdf->coordinate.map[p.x][p.y].color
					= find_color(*fdf, base, final, p);
			p.y++;
		}
		p.x++;
	}
}
void	earth_color(t_data *fdf)
{
	t_offset	p;

	p.y = 0;
	while (p.y < fdf->coordinate.maxy)
	{
		p.x = 0;
		while (p.x < fdf->coordinate.maxx)
		{
			int z = fdf->coordinate.map[p.y][p.x].z;

			if (z <= -10)
					fdf->coordinate.map[p.y][p.x].color = 0x00008B;
			else if (z > -10 && z <= 0)
					fdf->coordinate.map[p.y][p.x].color = 0x1E90FF;
			else if (z > 0 && z <= 5)
					fdf->coordinate.map[p.y][p.x].color = 0xF4A460;
			else if (z > 5 && z <= 20)
					fdf->coordinate.map[p.y][p.x].color = 0x00FF00;
			else if (z > 20 && z <= 50)
					fdf->coordinate.map[p.y][p.x].color = 0x008000;
			else if (z > 50 && z <= 100)
					fdf->coordinate.map[p.y][p.x].color = 0x8B4513;
			else if (z > 100 && z <= 200)
					fdf->coordinate.map[p.y][p.x].color = 0xA9A9A9;
			else
					fdf->coordinate.map[p.y][p.x].color = 0xFFFFFF;
			p.x++;
		}
		p.y++;
	}
}


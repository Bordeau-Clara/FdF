/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:56:42 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/22 15:04:35 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	interpolate_color(int color1, int color2, int length, int pixels)
{
	t_rgb	colora;
	t_rgb	colorb;
	t_rgb	color;
	float	t;

	if (length == 0)
		t = 0;
	else
		t = (float)(length - pixels) / length;
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

	if (fdf.coordinate[p.x][p.y].z <= fdf.minz)
		return (base);
	if (fdf.coordinate[p.x][p.y].z >= fdf.maxz)
		return (final);
	ratio = (float)(fdf.coordinate[p.x][p.y].z - fdf.minz) / \
		(fdf.maxz - fdf.minz);
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

void	change_color(t_data *fdf, int base, int final)
{
	t_offset	p;

	p.x = 0;
	while (p.x < fdf->maxy)
	{
		p.y = 0;
		while (p.y < fdf->maxx)
		{
			if (fdf->coordinate[p.x][p.y].z == fdf->minz)
				fdf->coordinate[p.x][p.y].color = base;
			else
				fdf->coordinate[p.x][p.y].color
					= find_color(*fdf, base, final, p);
			p.y++;
		}
		p.x++;
	}
}

void	earth(t_data *fdf, t_offset p, int z)
{
	if (z <= -10)
			fdf->coordinate[p.y][p.x].color = 0x00008B;
	else if (z > -10 && z <= 0)
			fdf->coordinate[p.y][p.x].color = 0x1E90FF;
	else if (z > 0 && z <= 5)
			fdf->coordinate[p.y][p.x].color = 0xF4A460;
	else if (z > 5 && z <= 20)
			fdf->coordinate[p.y][p.x].color = 0x00FF00;
	else if (z > 20 && z <= 50)
			fdf->coordinate[p.y][p.x].color = 0x008000;
	else if (z > 50 && z <= 100)
			fdf->coordinate[p.y][p.x].color = 0x8B4513;
	else if (z > 100 && z <= 200)
			fdf->coordinate[p.y][p.x].color = 0xA9A9A9;
	else
			fdf->coordinate[p.y][p.x].color = 0xFFFFFF;
}

void	earth_color(t_data *fdf)
{
	t_offset	p;
	int			z;

	p.y = 0;
	while (p.y < fdf->maxy)
	{
		p.x = 0;
		while (p.x < fdf->maxx)
		{
			z = fdf->coordinate[p.y][p.x].z;
			earth(fdf, p, z);
			p.x++;
		}
		p.y++;
	}
}

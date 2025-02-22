/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:03:24 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/22 15:37:35 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if ((x >= 0 && x < 1800 && y >= 0 && y < 1080) && color != 0)
	{
	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	}
}

int	is_in_window(t_point pixel)
{
	if (pixel.x < 0 || pixel.x > WINX)
		return (0);
	if (pixel.y < 0 || pixel.y > WINY)
		return (0);
	return (1);
}

void	ft_draw_line(t_data *fdf, t_point current, t_point next)
{
	t_point	delta;
	t_point	pixel;
	int		pixels;
	int		len;

	if (is_in_window(current) == 0 && is_in_window(next) == 0)
		return ;
	delta.x = next.x - current.x;
	delta.y = next.y - current.y;
	len = sqrt((delta.x * delta.x) + \
			(delta.y * delta.y));
	pixels = len;
	delta.x /= pixels;
	delta.y /= pixels;
	pixel.x = current.x;
	pixel.y = current.y;
	while (pixels > 0)
	{
		pixel.color = interpolate_color(current.color, next.color, len, pixels);
		my_mlx_pixel_put(fdf, pixel.x, pixel.y, pixel.color);
		pixel.x += delta.x;
		pixel.y += delta.y;
		pixels = pixels - 1;
	}
}

// Algorithme de Bresenham
// void	ft_draw_line(t_data *fdf, t_point current, t_point next)
// {
// 	int 	dx, dy, sx, sy, err, e2;
// 	int		length;
// 	int		step;
// 	int		color;
//
// 	step = 0;
// 	length
// 	= sqrt((next.x - current.x) * 
// 	(next.x - current.x) + 
// 			(next.y - current.y) * (next.y - current.y));
// 	dx = abs((int)next.x - (int)current.x);
// 	dy = abs((int)next.y - (int)current.y);
// 	if (current.x < next.x)
// 		sx = 1;
// 	else
// 		sx = -1;
// 	if (current.y < next.y)
// 		sy = 1;
// 	else
// 		sy = -1;
// 	err = dx - dy;
// 	while (TRUE)
// 	{
// 		color = interpolate_color(current.color, next.color, length, step);
// 		my_mlx_pixel_put(fdf, current.x, current.y, color);
// 		if (current.x == next.x && current.y == next.y)
// 			break ;
// 		e2 = 2 * err;
// 		if (e2 > -dy)
// 		{
// 			err -= dy;
// 			current.x += sx;
// 		}
// 		if (e2 < dx)
// 		{
// 			err += dx;
// 			current.y += sy;
// 		}
// 		step++;
// 	}
// 	my_mlx_pixel_put(fdf, current.x, current.y, current.color);
// 	my_mlx_pixel_put(fdf, next.x, next.y, next.color);
// }

void	display_controls(t_data *fdf)
{
	int	x;
	int	y;
	int	color;

	x = 1920 - 120;
	y = 20;
	color = 0xFFFFFF;
	mlx_string_put(fdf->mlx, fdf->win, x, y, color, " reset fdf :");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 20, color, "     R");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 40, color, " rotate X axis :");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 60, color, "    Q A");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 80, color, " rotate Y axis :");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 100, color, "    W S");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 120, color, " rotate Z axis :");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 140, color, "    E D");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 160, color, " projections :");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 180, color, "    0 1 2 3 4 5 c");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 200, color, " change colors :");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 220, color, "    Z X V");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 240, color, " change mode :");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 260, color, "    M");
}

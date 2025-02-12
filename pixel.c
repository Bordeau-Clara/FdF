/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:45:58 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/12 10:57:48 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if ((x >= 0 && x < 1920 && y >= 0 && y < 1080) && color != 0)
	{
	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	}
}

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

// Algorithme de Bresenham
void	ft_draw_line(t_data *data, t_point current, t_point next)
{
	int 	dx, dy, sx, sy, err, e2;
	int		length;
	int		step;
	float	t;
	int		color;

	step = 0;
	length = sqrt((next.x - current.x) * (next.x - current.x) + (next.y - current.y) * (next.y - current.y));
	dx = abs((int)next.x - (int)current.x);
	dy = abs((int)next.y - (int)current.y);
	if (current.x < next.x)
		sx = 1;
	else
		sx = -1;
	if (current.y < next.y)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (TRUE)
	{
		if (length == 0)
			t = 0;
		else
			t = (float)step / length;
		color = interpolate_color(current.color, next.color, t);
		my_mlx_pixel_put(data, current.x, current.y, color);
		if (current.x == next.x && current.y == next.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			current.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			current.y += sy;
		}
		step++;
	}
	my_mlx_pixel_put(data, current.x, current.y, current.color);
	my_mlx_pixel_put(data, next.x, next.y, next.color);
}

//algo qui fonctionne
//*void ft_draw_line(t_data *data, float x1, float y1, float x2, float y2, int color)*/
/*void ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color1, int color2)
{
    int step;
    int colour;
    double x, y;
    double delta_x, delta_y, delta_c;

    delta_x = x2 - x1;
    delta_y = y2 - y1;
    delta_c = color2 - color1;
    step = fmax(fabs(delta_x), fabs(delta_y)); // Utilisation de `fmax` pour éviter des erreurs

    delta_x /= step;
    delta_y /= step;
    delta_c /= step;

    x = x1;
    y = y1;
    colour = color1;

//attention pas de for	
    for (int i = 0; i <= step; i++)
    {
        my_mlx_pixel_put(data, round(x), round(y), colour);
        x += delta_x;
        y += delta_y;
	colour += delta_c;
    }
}*/

t_point	project_iso_bonus(t_data fdf, int x, int y)
{
	t_point		result;
	t_vector	rot;
	float		temp;

	rot.y = fdf.angle.cosx * y - fdf.angle.sinx * fdf.coordinate.map[y][x].z;
	rot.z = fdf.angle.sinx * y + fdf.angle.cosx * fdf.coordinate.map[y][x].z;
	rot.x = (fdf.angle.cosy) * x + fdf.angle.siny * rot.z;
	rot.z = -fdf.angle.siny * x + fdf.angle.cosy * rot.z;
	temp = rot.x;
	rot.x = fdf.angle.cosz * rot.x - fdf.angle.sinz * rot.y;
	rot.y = fdf.angle.sinz * temp + fdf.angle.cosz * rot.y;
	result.x = round(fdf.translatex + fdf.offset.x + (fdf.step * rot.x));
	result.y = round(fdf.translatey + fdf.offset.y + (fdf.step * rot.y));
	result.color = fdf.coordinate.map[y][x].color;
	return (result);
}

t_point	project_3d_to_2d(int x, int y, int z, t_data fdf)
{
	t_point		result;
	t_vector	rot;
	float		temp;

	rot.y = fdf.angle.cosx * y - fdf.angle.sinx * z;
	rot.z = fdf.angle.sinx * y + fdf.angle.cosx * z;
	rot.x = (fdf.angle.cosy) * x + fdf.angle.siny * rot.z;
	rot.z = -fdf.angle.siny * x + fdf.angle.cosy * rot.z;
	temp = rot.x;
	rot.x = fdf.angle.cosz * rot.x - fdf.angle.sinz * rot.y;
	rot.y = fdf.angle.sinz * temp + fdf.angle.cosz * rot.y;
	result.x = (fdf.step * rot.x);
	result.y = (fdf.step * rot.y);
	return (result);
}

int	distance(int a, int b)
{
	return ((a + b) / 2);
}

t_offset	set_offset(t_data fdf)
{
	t_offset	offset;
	t_point		middle;

	middle = project_3d_to_2d(fdf.coordinate.maxx / 2, fdf.coordinate.maxy / 2, distance(fdf.coordinate.maxz, fdf.coordinate.minz), fdf);
	offset.x = 960 - round(middle.x);
	offset.y = 540 - round(middle.y);
	return (offset);
}

void	set_angle(t_data *fdf)
{
	fdf->angle.cosx = cos(fdf->angle.x);
	fdf->angle.sinx = sin(fdf->angle.x);
	fdf->angle.cosy = cos(fdf->angle.y);
	fdf->angle.siny = sin(fdf->angle.y);
	fdf->angle.cosz = cos(fdf->angle.z);
	fdf->angle.sinz = sin(fdf->angle.z);
}

void	ft_draw_square(t_data *fdf, t_coordinate coordinate, int x, int y)
{
	t_point	next;
	t_point	current;

	set_angle(fdf);
	fdf->offset = set_offset(*fdf);
	while (x < coordinate.maxx)
	{
		y = 0;
		while (y < coordinate.maxy)
		{
			current = project_iso_bonus(*fdf, x, y);
			if (x < coordinate.maxx - 1)
			{
				next = project_iso_bonus(*fdf, x + 1, y);
				ft_draw_line(fdf, current, next);
			}
			if (y < coordinate.maxy - 1)
			{
				next = project_iso_bonus(*fdf, x, y + 1);
				ft_draw_line(fdf, current, next);
			}
			y++;
		}
		x++;
	}
}

int	exit_fdf(t_data *fdf)
{
	liberator_int_tab(fdf->coordinate.map, fdf->coordinate.maxy);
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->mlx_win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	exit(0);
}

int	main(int ac, char **av)
{
	t_data	fdf;

	(void)ac;
	dup_map(av[1], &fdf);
	fdf.save = dup_fdf(fdf.coordinate);
	fdf.mlx = mlx_init();
	fdf.mlx_win = mlx_new_window(fdf.mlx, 1920, 1080, "Square");
	fdf.img = mlx_new_image(fdf.mlx, 1920, 1080);
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bits_per_pixel, &fdf.line_lenght, &fdf.endian);
	
	fdf.step = 2;
	fdf.translatex = 0;
	fdf.translatey = 0;
	fdf.offset.x = 0;
	fdf.offset.y = 0;
	fdf.angle.x = 0;
	fdf.angle.y = 0;
	fdf.angle.z = 0;

	mlx_hook(fdf.mlx_win, 2, 1L << 0, key_hook, &fdf);
	mlx_mouse_hook(fdf.mlx_win, mouse_press, &fdf);
	mlx_hook(fdf.mlx_win, 17, 1L << 0, exit_fdf, &fdf);
	mlx_loop(fdf.mlx);
	liberator_int_tab(fdf.coordinate.map, fdf.coordinate.maxy);
}

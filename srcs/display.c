/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:03:24 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/19 08:05:29 by cbordeau         ###   ########.fr       */
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

// Algorithme de Bresenham
void	ft_draw_line(t_data *data, t_point current, t_point next)
{
	int 	dx, dy, sx, sy, err, e2;
	int		length;
	int		step;
	float	t;
	int		color;

	step = 0;
	length = sqrt((next.x - current.x) * (next.x - current.x) + \
			(next.y - current.y) * (next.y - current.y));
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

void	display_controls(t_data *fdf)
{
	int	x;
	int	y;
	int	color;

	x = 1920 - 120;
	y = 20;
	color = 0xFFFFFF;
	mlx_string_put(fdf->mlx, fdf->win, x, y, color, "reset fdf :");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 20, color, "     r");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 40, color, "rotate x axis :");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 60, color, "    q a");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 80, color, "rotate y axis :");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 100, color, "    w s");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 120, color, "rotate z axis :");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 140, color, "    e d");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 160, color, "pov on top :");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 180, color, "    0");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 200, color, "pov iso :");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 220, color, "    1");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 240, color, "change colors :");
	mlx_string_put(fdf->mlx, fdf->win, x, y + 260, color, "    z x");
}

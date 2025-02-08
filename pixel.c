/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:45:58 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/08 10:57:05 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	//printf("sx is %d, sy is %d\n", x, y);
	if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
	{
	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
void ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color1, int color2)
{
    int dx, dy, sx, sy, err, e2;
    int	length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2- y1));
    int	step = 0;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = (x1 < x2) ? 1 : -1;
    sy = (y1 < y2) ? 1 : -1;
    err = dx - dy;

    while (1)
    {
	float t = (length == 0) ? 0 : (float)step / length;
	int color = interpolate_color(color1, color2, t);
        my_mlx_pixel_put(data, x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
	step++;
    }
    my_mlx_pixel_put(data, x1, y1, color1);
    my_mlx_pixel_put(data, x2, y2, color2);
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

float	x2D(float x, float y, int step)
{
	float angle = M_PI / 6;
	float sx = 1000 + (step * ((x * cos(angle) - y * cos(angle))));
	return (sx);
}

float	y2D(float x, float y, float z, int step)
{
	float angle = M_PI / 6;
	float sy = 0 + (step * ((x * sin(angle) + y * sin(angle) - z)));
	return (sy);
}

/*void	ft_draw_square(t_data *img, t_coordinate coordinate, int x, int y, t_point point)
{
	t_point	nextx;
	t_point	nexty;
	int	color1;
	int	color2;

	if (coordinate.map[y][x + 1].z != 0)
		color2 = 0x00FF0000;
	else
		color2 = 0x000000FF;
	if (coordinate.map[y][x].z != 0)
		color1 = 0x00FF0000;
	else
		color1 = 0x000000FF;
	if (x < coordinate.maxx - 1)
	{
		nextx.step = point.step;
		nextx.x = x2D(x + 1, y, nextx.step);
		nextx.y = y2D(x + 1, y, coordinate.map[y][x + 1].z, nextx.step);
		ft_draw_line(img, point.x, point.y, nextx.x, nextx.y, color1, color2);
		ft_draw_square(img, coordinate, x + 1, y, nextx);
	}
	if (y < coordinate.maxy - 1)
	{
		nexty.step = point.step;
		nexty.x = x2D(x, y + 1, nexty.step);
		nexty.y = y2D(x, y + 1, coordinate.map[y + 1][x].z, nexty.step);
		ft_draw_line(img, point.x, point.y, nexty.x, nexty.y, color1, color2);
		ft_draw_square(img, coordinate, x, y + 1, nexty);
	}
}*/
t_point project_iso_bonus(t_data fdf, int x, int y)
{
    t_point result;
    double x_rot, y_rot, z_rot;
    double x_temp, y_temp, z_temp;
    
    // Coordonnées initiales
    double x0 = x;
    double y0 = y;
    double z0 = fdf.coordinate.map[y][x].z;

    // Rotation autour de l'axe X (pitch = π/2)
    y_temp = cos(fdf.angle.x) * y0 - sin(fdf.angle.x) * z0;
    z_temp = sin(fdf.angle.x) * y0 + cos(fdf.angle.x) * z0;
    y_rot = y_temp;
    z_rot = z_temp;

    // Rotation autour de l'axe Y (yaw = 0)
    x_temp = cos(fdf.angle.y) * x0 + sin(fdf.angle.y) * z_rot;
    z_temp = -sin(fdf.angle.y) * x0 + cos(fdf.angle.y) * z_rot;
    x_rot = x_temp;
    z_rot = z_temp;

    // Rotation autour de l'axe Z (roll = 0)
    x_temp = cos(fdf.angle.z) * x_rot - sin(fdf.angle.z) * y_rot;
    y_temp = sin(fdf.angle.z) * x_rot + cos(fdf.angle.z) * y_rot;
    x_rot = x_temp;
    y_rot = y_temp;

    // Dans une vue de dessus, on peut décider de simplement utiliser les coordonnées tournées
    result.x = fdf.translatex + fdf.offset.x + (fdf.step * x_rot);
    result.y = fdf.translatey + fdf.offset.y + (fdf.step * y_rot);
    result.color = fdf.coordinate.map[y][x].color;

    return result;
}

t_point	project_3d_to_2d(int x, int y, int z, t_data fdf)
{
    t_point result;
    double x_rot, y_rot, z_rot;
    double x_temp, y_temp, z_temp;

    // Rotation autour de X (Pitch)
    y_temp = cos(fdf.angle.x) * y - sin(fdf.angle.x) * z;
    z_temp = sin(fdf.angle.x) * y + cos(fdf.angle.x) * z;
    y_rot = y_temp;
    z_rot = z_temp;

    // Rotation autour de Y (Yaw)
    x_temp = cos(fdf.angle.y) * x + sin(fdf.angle.y) * z_rot;
    z_temp = -sin(fdf.angle.y) * x + cos(fdf.angle.y) * z_rot;
    x_rot = x_temp;
    z_rot = z_temp;

    // Rotation autour de Z (Roll)
    x_temp = cos(fdf.angle.z) * x_rot - sin(fdf.angle.z) * y_rot;
    y_temp = sin(fdf.angle.z) * x_rot + cos(fdf.angle.z) * y_rot;
    x_rot = x_temp;
    y_rot = y_temp;

    // Projection 2D
    result.x = (fdf.step * x_rot);
    result.y = (fdf.step * y_rot);

    return result;
}

t_offset	set_offset(t_data fdf)
{
	t_offset	offset;
	t_point		middle;
	
	middle = project_3d_to_2d(fdf.coordinate.maxx / 2, fdf.coordinate.maxy / 2, 0, fdf);
	offset.x = 960 - middle.x;
	offset.y = 540 - middle.y;
	//ft_draw_line(&fdf, 0, 0, middle.x + offset.x, middle.y + offset.y, 0x0, 0xFFFFFF);
	return (offset);
}

void	ft_draw_square(t_data *fdf, t_coordinate coordinate, int x, int y)
{
	t_point	next;
	t_point	current;

	fdf->offset = set_offset(*fdf);
	while(x < coordinate.maxx)
	{
		y = 0;
		while (y < coordinate.maxy)
		{
			current = project_iso_bonus(*fdf, x, y);
			if (x < coordinate.maxx - 1)
			{
				next = project_iso_bonus(*fdf, x + 1, y);
				ft_draw_line(fdf, current.x, current.y, next.x, next.y, current.color, next.color);
			}
			if (y < coordinate.maxy - 1)
			{
				next = project_iso_bonus(*fdf, x, y + 1);
				ft_draw_line(fdf, current.x, current.y, next.x, next.y, current.color, next.color);
			}
			y++;
		}
		x++;
	}
}

int	main(int ac, char **av)
{
	t_data	fdf;

	(void)ac;
	fdf.coordinate = dup_map(av[1]);
	fdf.mlx = mlx_init();
	fdf.mlx_win = mlx_new_window(fdf.mlx, 1920, 1080, "Square");
	fdf.img = mlx_new_image(fdf.mlx, 1920, 1080);
	fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bits_per_pixel, &fdf.line_lenght, &fdf.endian);
	
	fdf.step = 2;
	fdf.translatex = 0, fdf.translatey = 0;
	fdf.offset.x = 0, fdf.offset.y = 0;
	fdf.angle.x = 0, fdf.angle.y = 0, fdf.angle.z = 0;

	mlx_hook(fdf.mlx_win, 2, 1L << 0, key_hook, &fdf);
	mlx_mouse_hook(fdf.mlx_win, mouse_press, &fdf);
	mlx_loop(fdf.mlx);
	liberator_int_tab(fdf.coordinate.map, fdf.coordinate.maxy);
}

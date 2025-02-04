/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:45:58 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/04 14:17:37 by cbordeau         ###   ########.fr       */
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
	float sx = 200 + (step * ((x * cos(angle) - y * cos(angle))));
	return (sx);
}

float	y2D(float x, float y, float z, int step)
{
	float angle = M_PI / 6;
	float sy = 300 + (step * ((x * sin(angle) + y * sin(angle) - z)));
	return (sy);
}
void	ft_draw_square(t_data *img, t_coordinate coordinate, int x, int y, t_point point)
{
	t_point	nextx;
	t_point	nexty;
	int	color1;
	int	color2;

	if (coordinate.map[y][x + 1] != 0)
		color2 = 0x00FF0000;
	else
		color2 = 0x000000FF;
	if (coordinate.map[y][x] != 0)
		color1 = 0x00FF0000;
	else
		color1 = 0x000000FF;
	if (x < coordinate.maxx - 1)
	{
		nextx.step = point.step;
		nextx.x = x2D(x + 1, y, nextx.step);
		nextx.y = y2D(x + 1, y, coordinate.map[y][x + 1], nextx.step);
		ft_draw_line(img, point.x, point.y, nextx.x, nextx.y, color1, color2);
		ft_draw_square(img, coordinate, x + 1, y, nextx);
	}
	if (y < coordinate.maxy - 1)
	{
		nexty.step = point.step;
		nexty.x = x2D(x, y + 1, nexty.step);
		nexty.y = y2D(x, y + 1, coordinate.map[y + 1][x], nexty.step);
		ft_draw_line(img, point.x, point.y, nexty.x, nexty.y, color1, color2);
		ft_draw_square(img, coordinate, x, y + 1, nexty);
	}
}

int	main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_coordinate	coordinate;
	t_point	point;

	(void)ac;
	coordinate = dup_map(av[1]);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Square");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght, &img.endian);
	

	int x = 0;
	int y = 0;
	float angle = M_PI / 6;
	point.step = 20;
	point.x = (point.step * (x * cos(angle) - y * cos(angle))) + 200;
	point.y = (point.step * (x * sin(angle) + y * sin(angle) - (coordinate.map)[y][x])) + 300;
	int occurencex = coordinate.maxx;
	int occurencey = coordinate.maxy;
	printf("occurencex is %d, occurencey is %d\n", occurencex, occurencey);
	/*for (int i = 0; i < 50; i++)
	{
		ft_draw_line(&img, 50, 50 + i, 500, 50 + i, 0x000000FF, 0x00FF0000);
	}*/
	ft_draw_square(&img, coordinate, x, y, point);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

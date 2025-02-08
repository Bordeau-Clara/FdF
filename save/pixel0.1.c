/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:45:58 by cbordeau          #+#    #+#             */
/*   Updated: 2025/01/31 10:15:09 by cbordeau         ###   ########.fr       */
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

// Algorithme de Bresenham
void ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color)
{
    int dx, dy, sx, sy, err, e2;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = (x1 < x2) ? 1 : -1;
    sy = (y1 < y2) ? 1 : -1;
    err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(data, x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

//algo qui fonctionne
/*void ft_draw_line(t_data *data, float x1, float y1, float x2, float y2, int color)
{
    int step;
    double x, y;
    double delta_x, delta_y;

    delta_x = x2 - x1;
    delta_y = y2 - y1;
    step = fmax(fabs(delta_x), fabs(delta_y)); // Utilisation de `fmax` pour éviter des erreurs

	printf("x1 is %f, y1 is %f\n", x1, y1);
	printf("x2 is %f, y2 is %f\n", x2, y2);
    delta_x /= step;
    delta_y /= step;

    x = x1;
    y = y1;

//attention pas de for	
    for (int i = 0; i <= step; i++)
    {
        my_mlx_pixel_put(data, round(x), round(y), color);
        x += delta_x;
        y += delta_y;
    }
}*/

float	x2D(float x, float y)
{
	float angle = M_PI / 6;
	float sx = 200 + (20 * ((x * cos(angle) - y * cos(angle))));
	return (sx);
}

float	y2D(float x, float y, float z)
{
	float angle = M_PI / 6;
	float sy = 300 + (20 * ((x * sin(angle) + y * sin(angle) - z)));
	return (sy);
}
void	ft_draw_square(t_data *img, t_coordinate coordinate, float sx, float sy, int occurencex, int occurencey, int step, int x, int y)
{
	if (x < occurencex - 1 && x * step < 1920)
	{
		//struct int x int y, calc next point
		ft_draw_line(img, sx, sy, x2D(x + 1, y), y2D(x + 1, y, (coordinate.map)[y][x + 1]), 0x00FF0000);
		ft_draw_square(img, coordinate, x2D(x + 1, y), y2D(x + 1, y, (coordinate.map)[y][x + 1]), occurencex, occurencey, step, x + 1, y);
	}
	if (y < occurencey - 1 && y * step < 1080)
	{
		ft_draw_line(img, sx, sy, x2D(x, y + 1), y2D(x, y + 1, (coordinate.map)[y + 1][x]), 0x0000FF00);
		ft_draw_square(img, coordinate, x2D(x, y + 1), y2D(x, y + 1, (coordinate.map)[y + 1][x]), occurencex, occurencey, step, x, y + 1);
	}
}

int	main(int ac, char **av)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_coordinate	coordinate;

	(void)ac;
	coordinate = dup_map(av[1]);
	(void)(coordinate.x);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Square");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght, &img.endian);
	

	int x = 0;
	int y = 0;
	float angle = M_PI / 6;
	float sx = (20 * (x * cos(angle) - y * cos(angle))) + 200;
	float sy = (20 * (x * sin(angle) + y * sin(angle) - (coordinate.map)[y][x])) + 300;
	int occurencex = coordinate.x;
	int occurencey = coordinate.y;
	int step = 100;
	printf("sx is %f, sy is %f\n", sx, sy);
	printf("occurencex is %d, occurencey is %d\n", occurencex, occurencey);
	ft_draw_square(&img, coordinate, sx, sy, occurencex, occurencey, step, x, y);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:06:45 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/21 19:30:58 by cbordeau         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	line(t_data *fdf, t_point current, int nx, int ny)
{
	t_point	next;

	next = project_iso_bonus(*fdf, nx, ny);
	if (next.paint == 1)
		ft_draw_line(fdf, current, next);
}

void	ft_draw_fdf(t_data *fdf, t_coordinate coordinate, int x, int y)
{
	t_point	current;

	set_angle(fdf);
	fdf->offset = set_offset(*fdf);
	while (x < coordinate.maxx)
	{
		y = -1;
		while (++y < coordinate.maxy)
		{
			current = project_iso_bonus(*fdf, x, y);
			if (current.paint == 1)
			{
				if (x < coordinate.maxx - 1)
					line(fdf, current, x + 1, y);
				if (y < coordinate.maxy - 1)
					line(fdf, current, x, y + 1);
				if (x < coordinate.maxx - 1 && y < coordinate.maxy - 1
					&& fdf->mode == 1)
					line(fdf, current, x + 1, y + 1);
				if (y < coordinate.maxy - 1 && x - 1 >= 0 && fdf->mode == 1)
					line(fdf, current, x - 1, y + 1);
			}
		}
		x++;
	}
}

void	init_fdf(t_data *fdf)
{
	fdf->mode = 0;
	fdf->shpere = 0;
	fdf->step = 2;
	fdf->translatex = 0;
	fdf->translatey = 0;
	fdf->offset.x = 0;
	fdf->offset.y = 0;
	fdf->angle.x = PI / 4;
	fdf->angle.y = -PI / 6;
	fdf->angle.z = -PI / 8;
	fdf->mlx = mlx_init();
	if (fdf->mlx == NULL)
		ft_exit(fdf, NULL, FAILURE);
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, "FdF");
	if (fdf->win == NULL)
		ft_exit(fdf, NULL, FAILURE);
	fdf->img = mlx_new_image(fdf->mlx, 1800, 1080);
	if (fdf->img == NULL)
		ft_exit(fdf, NULL, FAILURE);
	fdf->addr = mlx_get_data_addr(fdf->img,
			&fdf->bits_per_pixel, &fdf->line_lenght, &fdf->endian);
}

int	main(int ac, char **av)
{
	t_data	fdf;

	if (ac != 2)
		return (-1);
	fdf.save.map = NULL;
	fdf.coordinate.map = NULL;
	init_fdf(&fdf);
	dup_map(av[1], &fdf);
	fdf.save = dup_fdf(fdf.coordinate, -1, -1);
	if (!fdf.save.map)
		ft_exit(&fdf, NULL, FAILURE);
	display_controls(&fdf);
	mlx_hook(fdf.win, 2, 1L << 0, key_hook, &fdf);
	mlx_mouse_hook(fdf.win, mouse_press, &fdf);
	mlx_hook(fdf.win, 17, 1L << 0, exit_fdf, &fdf);
	mlx_loop(fdf.mlx);
	liberator_int_tab(fdf.coordinate.map, fdf.coordinate.maxy);
}

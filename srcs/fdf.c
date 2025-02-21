/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:06:45 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/21 09:41:26 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_point	project_iso_bonus(t_data fdf, int x, int y)
{
	t_point		result;
	t_vector	rot;
	float		temp;

	rot.y = fdf.angle.cosx * fdf.coordinate.map[y][x].y - fdf.angle.sinx * fdf.coordinate.map[y][x].z;
	rot.z = fdf.angle.sinx * fdf.coordinate.map[y][x].y + fdf.angle.cosx * fdf.coordinate.map[y][x].z;
	rot.x = (fdf.angle.cosy) * fdf.coordinate.map[y][x].x + fdf.angle.siny * rot.z;
	rot.z = -fdf.angle.siny * fdf.coordinate.map[y][x].x + fdf.angle.cosy * rot.z;
	temp = rot.x;
	rot.x = fdf.angle.cosz * rot.x - fdf.angle.sinz * rot.y;
	rot.y = fdf.angle.sinz * temp + fdf.angle.cosz * rot.y;
	result.paint = 1;
	if (fdf.shpere == 1)
	{
		if (rot.z < 0)
			result.paint = 0;
		result.x = round(fdf.translatex + 900 + (fdf.step * rot.x));
		result.y = round(fdf.translatey + 540 + (fdf.step * rot.y));
	}
	else
	{
		result.x = round(fdf.translatex + fdf.offset.x + (fdf.step * rot.x));
		result.y = round(fdf.translatey + fdf.offset.y + (fdf.step * rot.y));
	}
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
		y = 0;
		while (y < coordinate.maxy)
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
			y++;
		}
		x++;
	}
}

// void	ft_draw_fdf(t_data *fdf, t_coordinate coordinate, int x, int y)
// {
// 	t_point	current;
//
// 	set_angle(fdf);
// 	fdf->offset = set_offset(*fdf);
// 	while (x < coordinate.maxx)
// 	{
// 		y = 0;
// 		while (y < coordinate.maxy)
// 		{
// 			current = project_iso_bonus(*fdf, fdf->coordinate.map[y][x].x, fdf->coordinate.map[y][x].y);
// 			if (x < coordinate.maxx - 1)
// 				line(fdf, current, fdf->coordinate.map[y][x + 1].x , fdf->coordinate.map[y][x].y);
// 			if (y < coordinate.maxy - 1)
// 				line(fdf, current, fdf->coordinate.map[y][x].x, fdf->coordinate.map[y + 1][x].y);
// 			if (x < coordinate.maxx - 1 && y < coordinate.maxy - 1
// 				&& fdf->mode == 1)
// 				line(fdf, current, fdf->coordinate.map[y][x + 1].x, fdf->coordinate.map[y + 1][x].y);
// 			if (y < coordinate.maxy - 1 && x - 1 >= 0 && fdf->mode == 1)
// 				line(fdf, current, fdf->coordinate.map[y][x - 1].x, fdf->coordinate.map[y + 1][x].y);
// 			y++;
// 		}
// 		x++;
// 	}
// }

void	ft_exit(t_data *fdf, t_list *lst, int err_code)
{
	if (lst)
		ft_lstclear(&lst, free);
	liberator_int_tab(fdf->coordinate.map, fdf->coordinate.maxy);
	liberator_int_tab(fdf->save.map, fdf->coordinate.maxy);
	if (fdf->img)
		mlx_destroy_image(fdf->mlx, fdf->img);
	if (fdf->win)
		mlx_destroy_window(fdf->mlx, fdf->win);
	if (fdf->mlx)
	{
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
	exit(err_code);
}

int	exit_fdf(t_data *fdf)
{
	liberator_int_tab(fdf->coordinate.map, fdf->coordinate.maxy);
	liberator_int_tab(fdf->save.map, fdf->coordinate.maxy);
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	exit(0);
}

void	init_fdf(t_data *fdf)
{
	fdf->mode = 0;
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
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, "Square");
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
	fdf.save = dup_fdf(fdf.coordinate);
	if (!fdf.save.map)
		ft_exit(&fdf, NULL, FAILURE);
	print_int_tab(fdf.coordinate.map, fdf.coordinate.maxy, fdf.coordinate.maxx);
	display_controls(&fdf);
	

	mlx_hook(fdf.win, 2, 1L << 0, key_hook, &fdf);
	mlx_mouse_hook(fdf.win, mouse_press, &fdf);
	mlx_hook(fdf.win, 17, 1L << 0, exit_fdf, &fdf);
	mlx_loop(fdf.mlx);
	liberator_int_tab(fdf.coordinate.map, fdf.coordinate.maxy);
}

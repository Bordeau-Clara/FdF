/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 08:08:30 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/18 15:58:50 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	put_new_img(t_data *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, 1800, 1080);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_lenght, &fdf->endian);
	ft_draw_square(fdf, fdf->coordinate, 0, 0);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

void	put_sphere(t_data *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, 1800, 1080);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_lenght, &fdf->endian);
	ft_draw_square2(fdf, fdf->coordinate, 0, 0);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

t_coordinate	dup_fdf(t_coordinate coordinate)
{
	t_coordinate	save;
	int				i;
	int				j;

	i = -1;
	save.maxx = coordinate.maxx;
	save.maxy = coordinate.maxy;
	save.maxz = coordinate.maxz;
	save.minz = coordinate.minz;
	save.map = malloc(save.maxy * sizeof(t_z *));
	if (!save.map)
		return (save);
	while (++i < coordinate.maxy)
	{
		j = -1;
		save.map[i] = malloc(save.maxx * sizeof(t_z));
		if (!save.map[i])
			return (liberator_int_tab(save.map, i), save);
		while (++j < coordinate.maxx)
		{
			save.map[i][j].z = coordinate.map[i][j].z;
			save.map[i][j].color = coordinate.map[i][j].color;
		}
	}
	return (save);
}

void	restore(t_data *fdf)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	fdf->coordinate.maxx = fdf->save.maxx;
	fdf->coordinate.maxy = fdf->save.maxy;
	fdf->coordinate.maxz = fdf->save.maxz;
	fdf->coordinate.minz = fdf->save.minz;
	while (i < fdf->save.maxy)
	{
		j = 0;
		while (j < fdf->save.maxx)
		{
			fdf->coordinate.map[i][j].z = fdf->save.map[i][j].z;
			fdf->coordinate.map[i][j].color = fdf->save.map[i][j].color;
			j++;
		}
		i++;
	}
}


int	key_hook(int keycode, t_data *fdf)
{
	z(keycode, fdf);
	colors(keycode, fdf);
	translate(keycode, fdf);
	view(keycode, fdf);
	rotate(keycode, fdf);
	if (keycode == KEY_ESC)
		exit_fdf(fdf);
	if (keycode == KEY_SPACE)
	{
		ft_draw_square(fdf, fdf->coordinate, 0, 0);
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	}
	if (keycode == KEY_R)
	{
		restore(fdf);
		put_new_img(fdf);
	}
	if (keycode == KEY_M)
	{
		if (fdf->mode < 1)
		fdf->mode++;
		else
			fdf->mode--;
		put_new_img(fdf);
	}
	if (keycode == KEY_C)
		put_sphere(fdf);
	return (0);
}

int	mouse_press(int button, int x, int y, t_data *fdf)
{
	(void)x;
	(void)y;
	if (button == MOUSE_WHEEL_UP)
	{
		fdf->step++;
		put_new_img(fdf);
	}
	else if (button == MOUSE_WHEEL_DOWN)
	{
		fdf->step--;
		put_new_img(fdf);
	}
	return (0);
}

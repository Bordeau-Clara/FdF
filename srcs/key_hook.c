/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 08:08:30 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/22 09:32:42 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	put_new_img(t_data *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, 1800, 1080);
	fdf->addr = mlx_get_data_addr
		(fdf->img, &fdf->bits_per_pixel, &fdf->line_lenght, &fdf->endian);
	ft_draw_fdf(fdf, 0, 0);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

int	key_hook(int keycode, t_data *fdf)
{
	basics(keycode, fdf);
	z(keycode, fdf);
	colors(keycode, fdf);
	translate(keycode, fdf);
	view(keycode, fdf);
	rotate(keycode, fdf);
	if (keycode == KEY_ESC)
		exit_fdf(fdf);
	if (keycode == KEY_C && fdf->shpere == 0)
	{
		fdf->shpere = 1;
		set_angle2(fdf, -PI / 2, 0, 0);
		go_polar(fdf, 0, 0);
		put_new_img(fdf);
	}
	return (0);
}

void	basics(int keycode, t_data *fdf)
{
	if (keycode == KEY_SPACE)
	{
		ft_draw_fdf(fdf, 0, 0);
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	}
	if (keycode == KEY_R)
	{
		fdf->mode = 0;
		fdf->shpere = 0;
		set_angle2(fdf, PI / 4, -PI / 6, 0);
		restore(fdf);
		put_new_img(fdf);
	}
	if (keycode == KEY_M)
	{
		if (fdf->mode < 1)
			fdf->mode++;
		else
			fdf->mode = 0;
		put_new_img(fdf);
	}
	if (keycode == KEY_SPACE
		|| keycode == KEY_R
		|| keycode == KEY_M)
		put_new_img(fdf);
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

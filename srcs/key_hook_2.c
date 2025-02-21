/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:23:37 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/21 09:20:04 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	view(int keycode, t_data *fdf)
{
	if (keycode == KEY_0)
		set_angle2(fdf, 0, 0, 0);
	if (keycode == KEY_1)
		set_angle2(fdf, PI / 4, -PI / 6, 0);
	if (keycode == KEY_2)
		set_angle2(fdf, PI / 4, -PI / 6, -PI / 8);
	if (keycode == KEY_3)
		set_angle2(fdf, 0, PI / 6, PI / 6);
	if (keycode == KEY_4)
		set_angle2(fdf, -PI / 3, PI / 4, 0);
	if (keycode == KEY_5)
		set_angle2(fdf, -PI / 2, PI / 6, 0);
	if (keycode == KEY_0
		|| keycode == KEY_1
		|| keycode == KEY_2
		|| keycode == KEY_3
		|| keycode == KEY_4
		|| keycode == KEY_5)
		put_new_img(fdf);
}

void	rotate(int keycode, t_data *fdf)
{
	if (keycode == KEY_Q)
		fdf->angle.x += PI / 12;
	if (keycode == KEY_A)
		fdf->angle.x -= PI / 12;
	if (keycode == KEY_W)
		fdf->angle.y += PI / 12;
	if (keycode == KEY_S)
		fdf->angle.y -= PI / 12;
	if (keycode == KEY_E)
		fdf->angle.z += PI / 12;
	if (keycode == KEY_D)
		fdf->angle.z -= PI / 12;
	if (keycode == KEY_Q
		|| keycode == KEY_A
		|| keycode == KEY_W
		|| keycode == KEY_S
		|| keycode == KEY_E
		|| keycode == KEY_D)
		put_new_img(fdf);
}

void	translate(int keycode, t_data *fdf)
{
	if (keycode == KEY_UP)
	{
		fdf->translatey -= 10;
		put_new_img(fdf);
	}
	if (keycode == KEY_DOWN)
	{
		fdf->translatey += 10;
		put_new_img(fdf);
	}
	if (keycode == KEY_LEFT)
	{
		fdf->translatex -= 10;
		put_new_img(fdf);
	}
	if (keycode == KEY_RIGHT)
	{
		fdf->translatex += 10;
		put_new_img(fdf);
	}
}

void	colors(int keycode, t_data *fdf)
{
	if (keycode == KEY_Z)
	{
		change_color(fdf, 0x00000000, 0x00FFFFFF);
		put_new_img(fdf);
	}
	if (keycode == KEY_X)
	{
		change_color(fdf, 0x00FF0000, 0x00FFFFFF);
		put_new_img(fdf);
	}
}

void	z(int keycode, t_data *fdf)
{
	if (keycode == KEY_MINUS)
	{
		move_z(fdf, 0);
		put_new_img(fdf);
	}
	if (keycode == KEY_PLUS)
	{
		move_z(fdf, 1);
		put_new_img(fdf);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 08:08:30 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/08 14:27:27 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_new_img(t_data *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img); // Supprime l'image précédente
	fdf->img = mlx_new_image(fdf->mlx, 1920, 1080); // Crée une nouvelle image
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_lenght, &fdf->endian);
	ft_draw_square(fdf, fdf->coordinate, 0, 0);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img, 0, 0);
}

int	key_hook(int keycode, t_data *fdf)
{

	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_SPACE)
	{
		ft_draw_square(fdf, fdf->coordinate, 0, 0);
		mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img, 0, 0);
	}
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
	if (keycode == KEY_Q)
	{
		fdf->angle.x += PI / 12;
		put_new_img(fdf);
	}
	if (keycode == KEY_A)
	{
		fdf->angle.x -= PI / 12;
		put_new_img(fdf);
	}
	if (keycode == KEY_W)
	{
		fdf->angle.y += PI / 12;
		put_new_img(fdf);
	}
	if (keycode == KEY_S)
	{
		fdf->angle.y -= PI / 12;
		put_new_img(fdf);
	}
	if (keycode == KEY_E)
	{
		fdf->angle.z += PI / 12;
		put_new_img(fdf);
	}
	if (keycode == KEY_D)
	{
		fdf->angle.z -= PI / 12;
		put_new_img(fdf);
	}
	if (keycode == KEY_0)
	{
		fdf->angle.x = 0;
		fdf->angle.y = 0;
		fdf->angle.z = 0;
		put_new_img(fdf);
	}
	if (keycode == KEY_1) //projection isometrique classique
	{
		fdf->angle.x = PI / 4;
		fdf->angle.y = - PI / 6;
		fdf->angle.z = 0;
		put_new_img(fdf);
	}
	if (keycode == KEY_2) //projection isometrique classque avec rotation de l'axe z
	{
		fdf->angle.x = PI / 4;
		fdf->angle.y = - PI / 6;
		fdf->angle.z = - PI / 8;
		put_new_img(fdf);
	}
	if (keycode == KEY_3) //projection militaire
	{
		fdf->angle.x = 0;
		fdf->angle.y = PI / 6;
		fdf->angle.z = PI / 6;
		put_new_img(fdf);
	}
	if (keycode == KEY_4) //vue drone
	{
		fdf->angle.x = - PI / 3;
		fdf->angle.y = PI / 4;
		fdf->angle.z = 0;
		put_new_img(fdf);
	}
	if (keycode == KEY_5) //projection oblique
	{
		fdf->angle.x = - PI / 2;
		fdf->angle.y = PI / 6;
		fdf->angle.z = 0;
		put_new_img(fdf);
	}
	if (keycode == KEY_Z)
	{
		change_base_color(fdf, 0x00000000, 0x00FFFFFF);
		put_new_img(fdf);
	}
	if (keycode == KEY_X)
	{
		change_base_color(fdf, 0x00FF0000, 0x00FFFFFF);
		put_new_img(fdf);
	}
	return (0);
}

int mouse_press(int button, int x, int y, t_data *fdf)
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


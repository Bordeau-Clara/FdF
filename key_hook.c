/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 08:08:30 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/08 08:45:12 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_data *fdf)
{

	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_SPACE)
	{
		ft_draw_square(fdf, fdf->coordinate, 0, 0);
		mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->img, 0, 0);
	}
	return (0);
}


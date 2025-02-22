/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:58:05 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/22 09:29:49 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	ft_exit(t_data *fdf, t_list *lst, int err_code)
{
	if (lst)
		ft_lstclear(&lst, free);
	liberator_int_tab(fdf->coordinate, fdf->maxy);
	liberator_int_tab(fdf->save, fdf->maxy);
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
	liberator_int_tab(fdf->coordinate, fdf->maxy);
	liberator_int_tab(fdf->save, fdf->maxy);
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	exit(0);
}

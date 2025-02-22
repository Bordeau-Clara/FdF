/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 07:54:55 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/22 08:42:45 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	set_angle(t_data *fdf)
{
	fdf->angle.cosx = cos(fdf->angle.x);
	fdf->angle.sinx = sin(fdf->angle.x);
	fdf->angle.cosy = cos(fdf->angle.y);
	fdf->angle.siny = sin(fdf->angle.y);
	fdf->angle.cosz = cos(fdf->angle.z);
	fdf->angle.sinz = sin(fdf->angle.z);
}

void	set_angle2(t_data *fdf, float x, float y, float z)
{
		fdf->angle.x = x;
		fdf->angle.y = y;
		fdf->angle.z = z;
}

int	distance(int a, int b)
{
	return ((a + b) / 2);
}

t_offset	set_offset(t_data fdf)
{
	t_offset	offset;
	t_point		middle;

	middle = project_3d_to_2d(fdf.maxx / 2, fdf.maxy / \
				2, distance(fdf.maxz, fdf.minz), fdf);
	offset.x = 900 - round(middle.x);
	offset.y = 540 - round(middle.y);
	return (offset);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:17:22 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/22 09:24:49 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	spherize(t_data *fdf, int x, int y)
{
	fdf->coordinate[y][x].x = (fdf->circle.radius + \
		fdf->coordinate[y][x].z) * \
		cos(fdf->coordinate[y][x].polar[LONG]) * \
		sin(fdf->coordinate[y][x].polar[LAT]);
	fdf->coordinate[y][x].y = (fdf->circle.radius + \
		fdf->coordinate[y][x].z) * \
		sin(fdf->coordinate[y][x].polar[LONG]) * \
		sin(fdf->coordinate[y][x].polar[LAT]);
	fdf->coordinate[y][x].z = (fdf->circle.radius + \
		fdf->coordinate[y][x].z) * \
		cos(fdf->coordinate[y][x].polar[LAT]);
}

void	go_polar(t_data *fdf, int x, int y)
{
	fdf->circle.step[X] = (PI * 2) / (float)(((float)fdf->maxx) - 1);
	fdf->circle.step[Y] = PI / (float)((float)fdf->maxy);
	fdf->circle.radius = ((float)fdf->maxx) / (PI * 2);
	while (y < fdf->maxy)
	{
		x = 0;
		while (x < fdf->maxx)
		{
			fdf->coordinate[y][x].polar[LONG]
				= -(fdf->coordinate[y][x].x) * fdf->circle.step[X];
			if (fdf->coordinate[y][x].y > (float)fdf->maxy)
				fdf->coordinate[y][x].polar[LAT]
					= (fdf->coordinate[y][x].y + \
					((float)fdf->maxy)) \
					* fdf->circle.step[Y] - 0.5 * fdf->circle.step[Y];
			else
				fdf->coordinate[y][x].polar[LAT]
					= (fdf->coordinate[y][x].y + \
					((float)fdf->maxy) - 1) \
					* fdf->circle.step[Y] + 0.5 * fdf->circle.step[Y];
			spherize(fdf, x, y);
			x++;
		}
		y++;
	}
}

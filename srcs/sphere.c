/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:17:22 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/21 07:59:04 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	spherize(t_data *fdf, int x, int y)
{
	fdf->coordinate.map[y][x].x = (fdf->circle.radius + fdf->coordinate.map[y][x].z) * \
		cos(fdf->coordinate.map[y][x].polar[LONG]) * sin(fdf->coordinate.map[y][x].polar[LAT]);
	fdf->coordinate.map[y][x].y = (fdf->circle.radius + fdf->coordinate.map[y][x].z) * \
		sin(fdf->coordinate.map[y][x].polar[LONG]) * sin(fdf->coordinate.map[y][x].polar[LAT]);
	fdf->coordinate.map[y][x].z = (fdf->circle.radius + fdf->coordinate.map[y][x].z) * \
		cos(fdf->coordinate.map[y][x].polar[LAT]);
}

void	go_polar(t_data *fdf)
{
	int	y;
	int	x;

	fdf->circle.step[X] = (PI * 2) / (float)(((float)fdf->coordinate.maxx) - 1);
	fdf->circle.step[Y] = PI / (float)((float)fdf->coordinate.maxy);
	fdf->circle.radius = ((float)fdf->coordinate.maxx) / (PI * 2);
	y = 0;
	while (y < fdf->coordinate.maxy)
	{
		x = 0;
		while (x < fdf->coordinate.maxx)
		{
			fdf->coordinate.map[y][x].polar[LONG] = -(fdf->coordinate.map[y][x].x) * fdf->circle.step[X];
			if ( fdf->coordinate.map[y][x].y > (float)fdf->coordinate.maxy)
				fdf->coordinate.map[y][x].polar[LAT] = (fdf->coordinate.map[y][x].y + \
					((float)fdf->coordinate.maxy)) * fdf->circle.step[Y] - 0.5 * fdf->circle.step[Y];
			else
				fdf->coordinate.map[y][x].polar[LAT] = (fdf->coordinate.map[y][x].y + \
					((float)fdf->coordinate.maxy) - 1) * fdf->circle.step[Y] + 0.5 * fdf->circle.step[Y];
			spherize(fdf, x, y);
			x++;
		}
		y++;
	}
}

// void	ft_draw_square2(t_data *fdf, t_coordinate coordinate, int x, int y)
// {
// 	t_point	next;
// 	t_point	current;
//
// 	set_angle(fdf);
// 	fdf->offset = set_offset(*fdf);
// 	while (x < coordinate.maxx)
// 	{
// 		y = 0;
// 		while (y < coordinate.maxy)
// 		{
// 			current = project_stereographic(*fdf, x, y);
// 			if (x < coordinate.maxx - 1)
// 			{
// 				next = project_stereographic(*fdf, x + 1, y);
// 				ft_draw_line(fdf, current, next);
// 			}
// 			if (y < coordinate.maxy - 1)
// 			{
// 				next = project_stereographic(*fdf, x, y + 1);
// 				ft_draw_line(fdf, current, next);
// 			}
// 			y++;
// 		}
// 		x++;
// 	}
// }

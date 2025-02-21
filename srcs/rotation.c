/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:03:47 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/21 18:53:06 by cbordeau         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_point	find_final_point(t_data fdf, t_vector rot)
{
	t_point	result;

	result.paint = 1;
	if (fdf.shpere == 1)
	{
		if (rot.z > 0)
			result.paint = 0;
		result.x = round(fdf.translatex + 900 + (fdf.step * rot.x));
		result.y = round(fdf.translatey + 540 + (fdf.step * rot.y));
	}
	else
	{
		result.x = round(fdf.translatex + fdf.offset.x + (fdf.step * rot.x));
		result.y = round(fdf.translatey + fdf.offset.y + (fdf.step * rot.y));
	}
	return (result);
}

t_point	project_iso_bonus(t_data fdf, int x, int y)
{
	t_point		result;
	t_vector	rot;
	float		temp;

	rot.y = fdf.angle.cosx * fdf.coordinate.map[y][x].y - \
		fdf.angle.sinx * fdf.coordinate.map[y][x].z;
	rot.z = fdf.angle.sinx * fdf.coordinate.map[y][x].y + \
		fdf.angle.cosx * fdf.coordinate.map[y][x].z;
	rot.x = (fdf.angle.cosy) * fdf.coordinate.map[y][x].x + \
		fdf.angle.siny * rot.z;
	rot.z = -fdf.angle.siny * fdf.coordinate.map[y][x].x + \
		fdf.angle.cosy * rot.z;
	temp = rot.x;
	rot.x = fdf.angle.cosz * rot.x - fdf.angle.sinz * rot.y;
	rot.y = fdf.angle.sinz * temp + fdf.angle.cosz * rot.y;
	result = find_final_point(fdf, rot);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:02:53 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/21 09:26:59 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_z
{
	float	x;
	float	y;
	float	z;
	float	polar[2];
	int		color;
	int		colorh;
}	t_z;

typedef struct s_coordinate
{
	t_z	**map;
	int	maxx;
	int	maxy;
	int	minz;
	int	maxz;
}	t_coordinate;

typedef struct s_angle
{
	float	x;
	float	cosx;
	float	sinx;
	float	y;
	float	cosy;
	float	siny;
	float	z;
	float	cosz;
	float	sinz;
}	t_angle;

typedef struct s_offset
{
	int	x;
	int	y;
}	t_offset;

typedef struct s_circle
{
	float	radius;
	float	step[2];
}	t_circle ;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_lenght;
	int				endian;
	void			*mlx;
	void			*win;

	t_coordinate	coordinate;
	t_coordinate	save;
	int				step;
	t_angle			angle;
	t_offset		offset;
	int				translatex;
	int				translatey;
	int				mode;
	int				shpere;
	t_circle		circle;
}	t_data;

typedef struct s_point
{
	float	x;
	float	y;
	int		paint;
	int		color;
}	t_point;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

#endif

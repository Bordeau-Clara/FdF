/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:38:37 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/18 16:27:22 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx-linux/mlx.h"
# include <math.h>
# include "Libft/get_next_line.h"
# include "Libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "struct.h"
# include "define.h"

void			liberator_int_tab(t_z **tab, int line);
void			print_int_tab(t_z **tab, int y, int x);
void			fill_coordinate(t_list *lst, t_data *fdf);
int				count_words(const char *s, char *c);
void			dup_map(char *file, t_data *fdf);
t_coordinate	dup_fdf(t_coordinate coordinate);

int				key_hook(int keycode, t_data *img);
int				mouse_press(int button, int x, int y, t_data *fdf);
void			put_new_img(t_data *fdf);
int				exit_fdf(t_data *fdf);
void			view(int keycode, t_data *fdf);
void			rotate(int keycode, t_data *fdf);
void			translate(int keycode, t_data *fdf);
void			colors(int keycode, t_data *fdf);
int				interpolate_color(int color1, int color2, float t);
void			z(int keycode, t_data *fdf);
void			change_color(t_data *fdf, int base, int final);
void			move_z(t_data *fdf, int mode);

void			ft_draw_square(t_data *img, t_coordinate coordinate, int x, int y);
void			ft_draw_line(t_data *data, t_point current, t_point next);
void			set_angle(t_data *fdf);
t_offset		set_offset(t_data fdf);

t_point			project_spherical(t_data fdf, int x, int y);
void			ft_draw_square2(t_data *fdf, t_coordinate coordinate, int x, int y);

#endif

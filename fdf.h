/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <cbordeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:38:37 by cbordeau          #+#    #+#             */
/*   Updated: 2025/02/21 12:29:43 by cbordeau         ###   ########.fr       */
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

//fdf
void			line(t_data *fdf, t_point current, int nx, int ny);
void			ft_draw_fdf(t_data *img, t_coordinate coordinate, int x, int y);
void			init_fdf(t_data *fdf);

//rotation
t_point			project_iso_bonus(t_data fdf, int x, int y);
t_point			project_3d_to_2d(int x, int y, int z, t_data fdf);

//display
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			ft_draw_line(t_data *data, t_point current, t_point next);
void			display_controls(t_data *fdf);

//key_hook
void			put_new_img(t_data *fdf);
int				key_hook(int keycode, t_data *img);
void			basics(int keycode, t_data *fdf);
int				mouse_press(int button, int x, int y, t_data *fdf);

//key_hook_2
void			view(int keycode, t_data *fdf);
void			rotate(int keycode, t_data *fdf);
void			translate(int keycode, t_data *fdf);
void			colors(int keycode, t_data *fdf);
void			z(int keycode, t_data *fdf);

//parsing_fdf
void			fill_coordinate(t_list *lst, t_data *fdf, int i, int j);
void			dup_map(char *file, t_data *fdf);

//parsing_utils
int				count_words(const char *s, char *c);
int				isbase(char c, char *base);
void			liberator_int_tab(t_z **tab, int line);
//void			print_int_tab(t_z **tab, int y, int x);

//exit
void			ft_exit(t_data *fdf, t_list *lst, int err_code);
int				exit_fdf(t_data *fdf);

//colors
int				interpolate_color(int color1, int color2, float t);
int				find_color(t_data fdf, int base, int final, t_offset p);
void			change_color(t_data *fdf, int base, int final);

//sphere
void			go_polar(t_data *fdf, int x, int y);

//utils
void			set_angle(t_data *fdf);
void			set_angle2(t_data *fdf, float x, float y, float z);
int				distance(int a, int b);
t_offset		set_offset(t_data fdf);

//utils_2
t_coordinate	dup_fdf(t_coordinate coordinate, int i, int j);
void			restore(t_data *fdf);
void			move_z(t_data *fdf, int mode);

#endif

#include "mlx.h"
#include <math.h>
#include "gnl/get_next_line.h"
#include "Libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

# define PI 3.14159265358979323846
# define KEY_ESC         65307
# define KEY_W           119
# define KEY_A           97
# define KEY_S           115
# define KEY_D           100
# define KEY_Q           113
# define KEY_E           101
# define KEY_Z           122
# define KEY_X           120
# define KEY_C           99
# define KEY_UP          65362
# define KEY_DOWN        65364
# define KEY_LEFT        65361
# define KEY_RIGHT       65363
# define KEY_PLUS        61
# define KEY_MINUS       45
# define KEY_1           49
# define KEY_2           50
# define KEY_3           51
# define KEY_4           52
# define KEY_5           53
# define KEY_6           54
# define KEY_7           55
# define KEY_8           56
# define KEY_9           57
# define KEY_0           48
# define KEY_SPACE       32
# define KEY_SHIFT       65505
# define KEY_CTRL        65507
# define KEY_ALT         65513
// Clavier principal
# define KEY_PLUS 61        // '+' sur clavier AZERTY
# define KEY_MINUS 45       // '-' sur clavier AZERTY

// Molette de la souris
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5

// Événements MLX
# define EVENT_KEY_PRESS 2
# define EVENT_KEY_RELEASE 3
# define EVENT_MOUSE_PRESS 4
# define EVENT_MOUSE_RELEASE 5
# define EVENT_DESTROY 17

typedef struct	s_z
{
	int	z;
	int	color;
	int	colorh;
}	t_z;

typedef struct s_coordinate
{
	t_z	**map;
	int	maxx;
	int	maxy;
	int	minz;
	int	maxz;
}	t_coordinate;

typedef	struct s_angle
{
	float	x;
	float	y;
	float	z;
}	t_angle;

typedef struct	s_offset
{
	int	x;
	int	y;
}	t_offset;

typedef struct  s_data
{
	void    *img;
	char    *addr;
	int     bits_per_pixel;
	int     line_lenght;
	int     endian;
	void	*mlx;
	void	*mlx_win;

	t_coordinate	coordinate;
	int		step;
	t_angle	angle;
	t_offset	offset;
	int	translatex;
	int	translatey;
}       t_data;


typedef struct	s_point
{
	float	x;
	float	y;
	int	color;
}	t_point;

typedef struct	s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

void			liberator_int_tab(t_z **tab, int line);
void			print_int_tab(t_z **tab, int y, int x);
t_coordinate	fill_coordinate(t_list *lst);
int				count_words(const char *s, char *c);
t_coordinate	dup_map(char *file);

int				key_hook(int keycode, t_data *img);
int 			mouse_press(int button, int x, int y, t_data *fdf);
void			change_base_color(t_data *fdf, int base, int final);

void			ft_draw_square(t_data *img, t_coordinate coordinate, int x, int y);
void			ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color1, int color2);

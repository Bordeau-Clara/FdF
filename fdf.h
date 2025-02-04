#include "mlx.h"
#include <math.h>
#include "gnl/get_next_line.h"
#include "Libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct  s_data
{
        void    *img;
        char    *addr;
        int     bits_per_pixel;
        int     line_lenght;
        int     endian;
}       t_data;

typedef struct s_coordinate
{
	int	**map;
	int	maxx;
	int	maxy;
}	t_coordinate;

typedef struct	s_z
{
	int	z;
	int	color;
}	t_z;
typedef struct	s_point
{
	float	x;
	float	y;
	int	color;
	int	step;
	int	offsetx;
	int	offsety;
}	t_point;

typedef struct	s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

void    liberator_int_tab(int **tab, int line);
void    print_int_tab(int **tab, int y, int x);
t_coordinate	fill_coordinate(t_list *lst);
int      count_words(const char *s, char *c);
t_coordinate    dup_map(char *file);

void    ft_draw_square(t_data *img, t_coordinate coordinate, int x, int y, t_point point);
void ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color1, int color2);

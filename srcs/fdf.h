/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:10:35 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/21 20:23:52 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_point_2d
{
	int	x;
	int	y;
}	t_point_2d;

typedef struct s_vector_2d
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_vector_3d
{
	double	x;
	double	y;
	double	z;
	double	k;
}	t_vec;

typedef struct s_isoplane
{
	double	a;
	double	b;
	double	c;
	t_vec	n;
	double	n2;
	t_vec	e;
	t_vec	p;
	t_vec	q;
	t_vec	ep;
	t_vec	eq;
	double	ep2;
	double	eq2;
}	t_isoplane;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_data;
	int			**map_arr;
	int			**map_color;
	char		**is_color_reserved;
	t_vec2		**proj_arr;
	t_point_2d	**proj_points;
	double		max_x_proj;
	double		min_x_proj;
	double		max_y_proj;
	double		min_y_proj;
	t_isoplane	*pl;
	int			width;
	int			height;
	int			size_line;
	int			endian;
	int			bits_per_pixel;
	int			esc_cnt;
	int			malloc_option;
	int			map_err;
	int			ncol;
	int			nrow;
}	t_data;

// data.c
void	init_data(t_data *data, int malloc_option);
int		create_data(t_data *data, int width, int height);
void	clear_data(t_data *data);

// point.c
void	set_point_2d(t_point_2d *dest, t_point_2d const *src);

// vector_setting.c
void	setvec2(t_vec2 *vec2, double x, double y);
void	setvec_xyz(t_vec *vec, double x, double y, double z);
void	setvec_k(t_vec *vec, double k);
void	setvec_vec(t_vec *vec, t_vec const *src);

// vector_operations.c
t_vec	prod(double k, t_vec const vec);
t_vec	add(t_vec const v1, t_vec const v2);
t_vec	diff(t_vec const v1, t_vec const v2);
double	dot(t_vec const *v1, t_vec const *v2);

// finish_objects.c
int		finish_image(void *mlx_ptr, void **img_ptr);
int		finish_window(void *mlx_ptr, void **win_ptr);
int		finish_display(void **mlx_ptr);

// events.c
int		doifnothing(void *param);
int		doifesc(int keycode, t_data *param);

// draw_line.c
int		draw_line(t_point_2d const *p1, t_point_2d const *p2, \
				int color, t_data *data);
int		draw_line_dx_part1(t_point_2d const *p1, t_point_2d const *p2, \
				int color, t_data *data);
int		draw_line_dx_part2(t_point_2d const *p1, t_point_2d const *p2, \
				int color, t_data *data);
int		draw_line_dy_part1(t_point_2d const *p1, t_point_2d const *p2, \
				int color, t_data *data);
int		draw_line_dy_part2(t_point_2d const *p1, t_point_2d const *p2, \
				int color, t_data *data);

// draw_line_aux.c
int		color_point(int x, int y, int color, t_data *data);
int		write_error(void);

// adjust_points_for_draw_line.c
int		adjust_points_for_draw_line(t_point_2d *p1, t_point_2d *p2, \
							t_data *data);
int		doif_p2x_outofrange(t_point_2d *p1, t_point_2d *p2, \
							t_data *data);
int		doif_p2y_outofrange(t_point_2d *p1, t_point_2d *p2, \
							t_data *data);
int		doif_bothpoints_outofrange(t_point_2d *p1, t_point_2d *p2, \
							t_data *data);

// adjust_points_for_draw_line_aux1.c
int		is_point_inside(t_point_2d const *p, t_data *data);
int		does_line_intersect(t_point_2d const *p1, \
				t_point_2d const *p2, t_data *data);
double	get_side_of_line(int x, int y, double k, t_point_2d const *p);
int		ft_round(double num);
void	resizeapointifneeded(t_point_2d *point);

// adjust_points_for_draw_line_aux2.c
int		ft_abs(int x); // not used
void	swap(void **ptr1, void **ptr2); // not used

// read_input_aux.c
int		malloc_err(char const *str);
int		set_fd(int argc, char **argv, int *fd);
int		read_input_init_data(int argc, char **argv, t_data *data, \
								int *fd);
int		read_data_set_ncol_nrow(int argc, char **argv, \
					t_data *data, int *fd);
int		allocate_arr(t_data *data, void ***arr, int size);

// read_input.c
int		free_data_map_arr(t_data *data, void ***arr);
int		read_data_allocate_all_arrays(t_data *data);
int		read_data(int argc, char **argv, t_data *data, int *fd);
void	treat_num_color(char const *num_comma_color, int i, int j, \
							t_data *data);
void	print_data_map_arr(t_data *data);

//isoplane_setting.c
int		init_isoplane(t_isoplane **pl);
void	compute_ep_eq(t_isoplane *pl);
void	compute_p_q(t_isoplane *pl);
void	free_plane(t_isoplane **pl);

//isoplane_computing_part1.c
void	compute_projection_in_original_3d_space(t_isoplane const *pl, \
				t_vec const *vec, t_vec *res);
int		compute_all_projections(t_data *data);
int		compute_max_min_xy(t_data *data);

//isoplane_computing_part2.c
int		recompute_projected_points(t_data *data);
int		recompute_projected_points_x(t_data *data);
int		recompute_projected_points_y(t_data *data);
int		plot_projected_points(t_data *data);
void	connect_point_with_neighbors(t_data *data, int i, int j);

#endif /* FDF_H */

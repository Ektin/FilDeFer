/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isoplane_computing_part1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:52:37 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/20 23:43:04 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	compute_projection_in_original_3d_space(t_isoplane const *pl, \
		t_vec const *vec, t_vec *res)
{
	double	h;
	t_vec	tmp_vec;

	h = (pl->endot - dot(vec, &pl->n)) / pl->n2;
	tmp_vec = add(*vec, prod(h, pl->n));
	setvec_vec(res, &tmp_vec);
}

void	choose_mode_init(t_data *data, int mode)
{
	ft_printf("\n\n\n\nWe are never here in choose_mode_init,");
	ft_printf(" mode=[%d]\n\n\n\n", mode);
	if (1 == mode)
		init_isoplane(&data->pl, 1);
	else if (get_event_mode(XK_Right) == mode)
		rotate_right_isoplane(data->pl);
	else if (get_event_mode(XK_Left) == mode)
		rotate_left_isoplane(data->pl);
	else
		ft_printf("\n\nNonspecified mode in choose_mode_init\n\n");
}

void	compute_all_projections(t_data *data, int mode)
{
	int		i;
	int		j;
	t_vec	vec_space;
	t_vec	vec_proj;

	init_isoplane(&data->pl, mode);
	if (1 == mode)
		data->already_adjusted_proj = 0;
	i = -1;
	while (++i < data->nrow)
	{
		j = -1;
		while (++j < data->ncol)
		{
			setvec_xyz(&vec_space, j - data->ncol / 2, \
				i - data->nrow / 2, \
						data->map_arr[i][j]);
			compute_projection_in_original_3d_space(data->pl, &vec_space, \
				&vec_proj);
			vec_proj = diff(vec_proj, data->pl->e);
			setvec2(&data->proj_arr[i][j], dot(&vec_proj, \
				&data->pl->ep) / data->pl->ep1, \
				dot(&vec_proj, &data->pl->eq) / data->pl->eq1);
		}
	}
}

void	set_data_for_compute_max_min_xy(t_data *data)
{
	data->max_x_proj = data->proj_arr[0][0].x;
	data->min_x_proj = data->proj_arr[0][0].x;
	data->max_y_proj = data->proj_arr[0][0].y;
	data->min_y_proj = data->proj_arr[0][0].y;
	data->max_x_proj_i = 0;
	data->max_x_proj_j = 0;
	data->min_x_proj_i = 0;
	data->min_x_proj_j = 0;
	data->max_y_proj_i = 0;
	data->max_y_proj_j = 0;
	data->min_y_proj_i = 0;
	data->min_y_proj_j = 0;
}

int	compute_max_min_xy(t_data *data)
{
	int	i;
	int	j;

	set_data_for_compute_max_min_xy(data);
	i = -1;
	while (++i < data->nrow)
	{
		j = -1;
		while (++j < data->ncol)
		{
			if (data->max_x_proj < data->proj_arr[i][j].x)
			{
				set_max_x_proj(data, data->proj_arr[i][j].x, i, j);
			}
			else if (data->min_x_proj > data->proj_arr[i][j].x)
			{
				set_min_x_proj(data, data->proj_arr[i][j].x, i, j);
			}
			if (data->max_y_proj < data->proj_arr[i][j].y)
				set_max_y_proj(data, data->proj_arr[i][j].y, i, j);
			else if (data->min_y_proj > data->proj_arr[i][j].y)
				set_min_y_proj(data, data->proj_arr[i][j].y, i, j);
		}
	}
	return (0);
}

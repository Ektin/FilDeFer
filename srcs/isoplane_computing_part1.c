/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isoplane_computing_part1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:52:37 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/21 20:25:45 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	compute_projection_in_original_3d_space(t_isoplane const *pl, \
		t_vec const *vec, t_vec *res)
{
	double	h;
	t_vec	tmp_vec;

	h = (1.0 - dot(vec, &pl->n)) / pl->n2;
	tmp_vec = add(*vec, prod(h, pl->n));
	setvec_vec(res, &tmp_vec);
}

int	compute_all_projections(t_data *data)
{
	int		i;
	int		j;
	t_vec	vec_space;
	t_vec	vec_proj;

	init_isoplane(&data->pl);
	if (1 == allocate_arr(data, (void ***)&data->proj_arr, sizeof(t_vec2)))
		return (malloc_err("compute_all_projections"));
	i = -1;
	while (++i < data->nrow)
	{
		j = -1;
		while (++j < data->ncol)
		{
			setvec_xyz(&vec_space, j, i, data->map_arr[i][j]);
			compute_projection_in_original_3d_space(data->pl, &vec_space, \
				&vec_proj);
			vec_proj = diff(vec_proj, data->pl->e);
			setvec2(&data->proj_arr[i][j], dot(&vec_proj, \
				&data->pl->ep) / data->pl->ep2, \
				dot(&vec_proj, &data->pl->eq) / data->pl->eq2);
		}
	}
	return (0);
}

int	compute_max_min_xy(t_data *data)
{
	int	i;
	int	j;

	data->max_x_proj = data->proj_arr[0][0].x;
	data->min_x_proj = data->proj_arr[0][0].y;
	data->max_y_proj = data->proj_arr[0][0].x;
	data->min_y_proj = data->proj_arr[0][0].y;
	i = -1;
	while (++i < data->nrow)
	{
		j = -1;
		while (++j < data->ncol)
		{
			if (data->max_x_proj < data->proj_arr[i][j].x)
				data->max_x_proj = data->proj_arr[i][j].x;
			else if (data->min_x_proj > data->proj_arr[i][j].x)
				data->min_x_proj = data->proj_arr[i][j].x;
			if (data->max_y_proj < data->proj_arr[i][j].y)
				data->max_y_proj = data->proj_arr[i][j].y;
			else if (data->min_y_proj > data->proj_arr[i][j].y)
				data->min_y_proj = data->proj_arr[i][j].y;
		}
	}
	return (0);
}

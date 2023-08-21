/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isoplane_computing_part2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:52:37 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/21 20:25:25 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	recompute_projected_points(t_data *data)
{
	if (1 == compute_all_projections(data))
		return (malloc_err("compute_max_min_xy"));
	compute_max_min_xy(data);
	if (1 == allocate_arr(data, \
		(void ***)&data->proj_points, sizeof(**data->proj_points)))
		return (malloc_err("proj_points"));
	recompute_projected_points_x(data);
	recompute_projected_points_y(data);
	return (0);
}

int	recompute_projected_points_x(t_data *data)
{
	int		i;
	int		j;
	double	kx;
	double	bx;
	double	eps;

	eps = 0.01;
	kx = (double)data->width / (data->max_x_proj - data->min_x_proj + eps);
	bx = -kx * data->min_x_proj + eps;
	i = -1;
	while (++i < data->nrow)
	{
		j = -1;
		while (++j < data->ncol)
		{
			data->proj_points[i][j].x = \
				ft_round(data->proj_arr[i][j].x * kx + bx);
		}
	}
	return (0);
}

int	recompute_projected_points_y(t_data *data)
{
	int		i;
	int		j;
	double	ky;
	double	by;
	double	eps;

	eps = 0.01;
	ky = (double)data->height / (data->max_y_proj - data->min_y_proj + eps);
	by = -ky * data->min_y_proj + eps;
	i = -1;
	while (++i < data->nrow)
	{
		j = -1;
		while (++j < data->ncol)
		{
			data->proj_points[i][j].y = \
				ft_round(data->proj_arr[i][j].y * ky + by);
		}
	}
	return (0);
}

int	plot_projected_points(t_data *data)
{
	int	i;
	int	j;

	if (1 == recompute_projected_points(data))
		return (malloc_err("plot_projected_points"));
	i = -1;
	while (++i < data->nrow)
	{
		j = -1;
		while (++j < data->ncol)
		{
			connect_point_with_neighbors(data, i, j);
		}
	}
	return (0);
}

void	connect_point_with_neighbors(t_data *data, int i, int j)
{
	if (j + 1 < data->ncol)
		draw_line(&data->proj_points[i][j], \
			&data->proj_points[i][j + 1], 0xffffff, data);
	if (j > 0)
		draw_line(&data->proj_points[i][j], \
			&data->proj_points[i][j - 1], 0xffffff, data);
	if (i + 1 < data->nrow)
		draw_line(&data->proj_points[i][j], \
			&data->proj_points[i + 1][j], 0xffffff, data);
	if (i > 0)
		draw_line(&data->proj_points[i][j], \
			&data->proj_points[i - 1][j], 0xffffff, data);
}

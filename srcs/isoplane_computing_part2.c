/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isoplane_computing_part2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:52:37 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/22 17:31:38 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	resize_projected_points(t_data *data, int mode)
{
	compute_all_projections(data, mode);
	if (data->already_adjusted_proj == 0)
		compute_max_min_xy(data);
	if (0 == in_resize_proj_p_init_left_right_io(data, mode))
		return (0);
	else if (get_event_mode('a') == mode)
		shift_projected_points_x(-data->delta_bx, data);
	else if (get_event_mode('d') == mode)
		shift_projected_points_x(data->delta_bx, data);
	else if (get_event_mode('w') == mode)
		shift_projected_points_y(-data->delta_by, data);
	else if (get_event_mode('s') == mode)
		shift_projected_points_y(data->delta_by, data);
	else if (get_event_mode('c') == mode)
		shift_points_if_center_pressed(data);
	return (0);
}

int	in_resize_proj_p_init_left_right_io(t_data *data, int mode)
{
	if (1 <= mode && get_event_mode(XK_Down) >= mode)
	{
		determine_koef(data);
		resize_projected_points_x(data);
		resize_projected_points_y(data);
		return (0);
	}
	else if (get_event_mode('i') == mode || get_event_mode('o') == mode)
	{
		if (get_event_mode('i') == mode)
			data->k *= data->delta_k;
		else if (get_event_mode('o') == mode)
			data->k /= data->delta_k;
		resize_projected_points_x(data);
		resize_projected_points_y(data);
		return (0);
	}
	return (1);
}

/*double	determine_koef_obsolete(t_data *data)
{
	double	k;

	if (data->already_adjusted_proj == 1)
		return (data->k);
	k = -1.0;
	if (data->max_x_proj > 0)
		k = (data->width >> 1) / data->max_x_proj;
	if (data->min_x_proj < 0 && (k < 0 || \
			k > (data->width >> 1) / (-data->min_x_proj)))
		k = (data->width >> 1) / (-data->min_x_proj);
	if (data->max_y_proj > 0 && (k < 0 || \
		k > (data->height >> 1) / data->max_y_proj))
	{
		k = (data->height >> 1) / data->max_y_proj;
	}
	if (data->min_y_proj < 0 && (k < 0 || \
		k > (data->height >> 1) / (-data->min_y_proj)))
	{
		k = (data->height >> 1) / (-data->min_y_proj);
	}
	if (k < 0)
		ft_printf("\n\n\033[31mThis is impossible determine_koef\n\n");
	data->k = k;
	return (data->k);
}*/

void	determine_koef(t_data *data)
{
	double	eps;

	if (0 != data->already_adjusted_proj)
		return ;
	eps = 1e-6;
	data->kx = ((double)data->width - 1.0) / \
		(data->max_x_proj - data->min_x_proj + eps);
	data->ky = ((double)data->height - 1.0) / \
		(data->max_y_proj - data->min_y_proj + eps);
	if (data->k < 0 || 0 == data->fix_k)
	{
		data->k = data->kx;
		if (data->kx > data->ky)
			data->k = data->ky;
	}
	data->bx = 0.0;
	data->by = 0.0;
	data->bx = data->width / 2.0 - data->k / 2.0 * \
		(data->max_x_proj + data->min_x_proj);
	data->by = data->height / 2.0 - data->k / 2.0 * \
		(data->max_y_proj + data->min_y_proj);
}

int	resize_projected_points_x(t_data *data)
{
	int		i;
	int		j;
	double	eps;

	eps = 0.01;
	if (0 == 1 && 0 == data->already_adjusted_proj)
	{
		data->kx = data->k;
		data->bx = data->width >> 1;
		data->kx = ((double)data->width - 1.0) / \
			(data->max_x_proj - data->min_x_proj + eps);
		data->bx = -data->kx * data->min_x_proj;
	}
	i = -1;
	while (++i < data->nrow)
	{
		j = -1;
		while (++j < data->ncol)
		{
			data->proj_points[i][j].x = ft_round(data->proj_arr[i][j].x \
			* data->k + data->bx + data->shift_x);
		}
	}
	return (0);
}

int	resize_projected_points_y(t_data *data)
{
	int		i;
	int		j;
	double	eps;

	eps = 0.01;
	if (0 == 1 && 0 == data->already_adjusted_proj)
	{
		data->ky = data->k;
		data->by = data->height >> 1;
		data->ky = ((double)data->height - 1.0) / \
			(data->max_y_proj - data->min_y_proj + eps);
		data->by = -data->ky * data->min_y_proj;
	}
	i = -1;
	while (++i < data->nrow)
	{
		j = -1;
		while (++j < data->ncol)
		{
			data->proj_points[i][j].y = ft_round(data->proj_arr[i][j].y \
			* data->k + data->by + data->shift_y);
		}
	}
	return (0);
}

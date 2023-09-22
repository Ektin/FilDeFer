/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isoplane_computing_part3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:17:57 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/22 17:47:01 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
	mode:
		1: initial
		2: rotate right (phi+)
		3: rotate left (phi-)
		4,5,6,7: shift: left,right,up,down
*/
int	plot_projected_points(t_data *data, int mode)
{
	int	i;
	int	j;

	data->busy |= 1;
	resize_projected_points(data, mode);
	i = -1;
	while (++i < data->nrow)
	{
		j = -1;
		while (++j < data->ncol)
		{
			connect_point_with_neighbors(data, i, j);
		}
	}
	print_details_isoplane(data);
	data->busy &= 2;
	return (0);
}

void	connect_point_with_neighbors(t_data *data, int i, int j)
{
	if (j + 1 < data->ncol)
		draw_line(&data->proj_points[i][j], \
		&data->proj_points[i][j + 1], data->map_color[i][j], data);
	if (j > 0)
		draw_line(&data->proj_points[i][j], \
		&data->proj_points[i][j - 1], data->map_color[i][j], data);
	if (i + 1 < data->nrow)
		draw_line(&data->proj_points[i][j], \
		&data->proj_points[i + 1][j], data->map_color[i][j], data);
	if (i > 0)
		draw_line(&data->proj_points[i][j], \
		&data->proj_points[i - 1][j], data->map_color[i][j], data);
}

void	print_details_isoplane(t_data *data)
{
	if (0 == data->verbatim)
		return ;
	ft_printf("\n\nw:{%d},h:{%d}, ncol:{%d},nrow:{%d}; [adj=%d]", data->width, \
		data->height, data->ncol, data->nrow, data->already_adjusted_proj);
	ft_printf("\n\ndata x:[%f]--[%f], y: [%f]--[%f]\n\n", data->min_x_proj, \
		data->max_x_proj, data->min_y_proj, data->max_y_proj);
	ft_printf("min x: (%d, %d, %d); ", data->min_x_proj_i, data->min_x_proj_j, \
		data->map_arr[data->min_x_proj_i][data->min_x_proj_j]);
	ft_printf("max x: (%d, %d, %d); ", data->max_x_proj_i, data->max_x_proj_j, \
		data->map_arr[data->max_x_proj_i][data->max_x_proj_j]);
	ft_printf("min y: (%d, %d, %d); ", data->min_y_proj_i, data->min_y_proj_j, \
		data->map_arr[data->min_y_proj_i][data->min_y_proj_j]);
	ft_printf("max y: (%d, %d, %d);\n\n", data->max_y_proj_i, \
	data->max_y_proj_j, data->map_arr[data->max_y_proj_i][data->max_y_proj_j]);
	print_details_isoplane_part2(data);
}

void	print_details_isoplane_part2(t_data *data)
{
	ft_printf("k: [%f], kx:[%f], bx:[%f], shift_x:[%f], ", \
			data->k, data->kx, data->bx, data->shift_x);
	ft_printf("ky:[%f], by:[%f], shift_y:[%f]\n\n", \
		data->ky, data->by, data->shift_y);
	ft_printf("a:[%f], b:[%f], c:[%f]\n\n", data->pl->a, data->pl->b, \
						data->pl->c);
	ft_printf("phi:[%f], deltaphi:[%f], psi:[%f]\n\n", data->pl->phi, \
		data->pl->deltaphi, data->pl->psi);
	ft_printf("n:(%f, %f, %f), k:[%f], n2: [%f]\n\n", data->pl->n.x, \
		data->pl->n.y, data->pl->n.z, data->pl->n.k, data->pl->n2);
	ft_printf("EP:(%f, %f, %f), k:[%f], ep1: [%f]\n\n", data->pl->ep.x, \
		data->pl->ep.y, data->pl->ep.z, data->pl->ep.k, data->pl->ep1);
	ft_printf("EQ:(%f, %f, %f), k:[%f], eq1: [%f]\n\n", data->pl->eq.x, \
		data->pl->eq.y, data->pl->eq.z, data->pl->eq.k, data->pl->eq1);
	ft_printf("OE:(%f, %f, %f), k:[%f], OE*n:[%f]\n\n", data->pl->e.x, \
		data->pl->e.y, data->pl->e.z, data->pl->e.k, data->pl->endot);
}

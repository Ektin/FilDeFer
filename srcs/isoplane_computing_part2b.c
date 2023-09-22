/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isoplane_computing_part2b.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:52:37 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/22 15:33:47 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	shift_projected_points_x(double shift, t_data *data)
{
	int	i;
	int	j;

	data->shift_x += shift;
	i = -1;
	while (++i < data->nrow)
	{
		j = -1;
		while (++j < data->ncol)
		{
			data->proj_points[i][j].x += shift;
		}
	}
	return (0);
}

int	shift_projected_points_y(double shift, t_data *data)
{
	int	i;
	int	j;

	data->shift_y += shift;
	i = -1;
	while (++i < data->nrow)
	{
		j = -1;
		while (++j < data->ncol)
		{
			data->proj_points[i][j].y += shift;
		}
	}
	return (0);
}

int	shift_points_if_center_pressed(t_data *data)
{
	if (0.0 != data->shift_y)
		shift_projected_points_y(-data->shift_y, data);
	if (0.0 != data->shift_x)
		shift_projected_points_x(-data->shift_x, data);
	data->shift_x = 0.0;
	data->shift_y = 0.0;
	return (0);
}

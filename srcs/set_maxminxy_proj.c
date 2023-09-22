/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_maxminxy_proj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:02:13 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/18 18:02:32 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_max_x_proj(t_data *data, double d, int i, int j)
{
	data->max_x_proj = d;
	data->max_x_proj_i = i;
	data->max_x_proj_j = j;
}

void	set_min_x_proj(t_data *data, double d, int i, int j)
{
	data->min_x_proj = d;
	data->min_x_proj_i = i;
	data->min_x_proj_j = j;
}

void	set_max_y_proj(t_data *data, double d, int i, int j)
{
	data->max_y_proj = d;
	data->max_y_proj_i = i;
	data->max_y_proj_j = j;
}

void	set_min_y_proj(t_data *data, double d, int i, int j)
{
	data->min_y_proj = d;
	data->min_y_proj_i = i;
	data->min_y_proj_j = j;
}

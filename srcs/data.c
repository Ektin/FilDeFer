/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:06:13 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/22 14:50:10 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// to make busy option work one needs parallelism
void	init_data(t_data *data, int malloc_option)
{
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->img_ptr = NULL;
	data->img_data = NULL;
	data->map_arr = NULL;
	data->pl = NULL;
	data->esc_cnt = 0;
	data->destroy_cnt = 0;
	data->malloc_option = malloc_option;
	data->map_err = 0;
	data->ncol = 0;
	data->nrow = 0;
	data->already_adjusted_proj = 0;
	data->start_cnt = 0;
	data->end_cnt = 0;
	data->delta_k = 1.1;
	data->shift_x = 0.0;
	data->shift_y = 0.0;
	data->k = -1.0;
	data->fix_k = 1;
	data->verbatim = 0;
	data->busy = 0;
}

int	create_data(t_data *data, int width, int height)
{
	data->mlx_ptr = mlx_init();
	if (NULL == data->mlx_ptr)
		return (1);
	data->width = width;
	data->height = height;
	data->win_ptr = mlx_new_window(data->mlx_ptr, \
		data->width, data->height, "window");
	if (NULL == data->win_ptr)
		return (finish_display(&data->mlx_ptr));
	data->img_ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	if (NULL == data->win_ptr)
	{
		finish_window(data->mlx_ptr, &data->win_ptr);
		return (finish_display(&data->mlx_ptr));
	}
	data->img_data = mlx_get_data_addr(data->img_ptr, &data->bits_per_pixel, \
		&data->size_line, &data->endian);
	data->delta_bx = (double)(data->width) / 100.0;
	data->delta_by = (double)(data->height) / 100.0;
	return (0);
}

void	clear_data(t_data *data)
{
	if (NULL == data)
		return ;
	if (NULL != data->mlx_ptr && NULL != data->img_ptr)
		finish_image(data->mlx_ptr, &data->img_ptr);
	if (NULL != data->mlx_ptr && NULL != data->win_ptr)
		finish_window(data->mlx_ptr, &data->win_ptr);
	data->img_data = NULL;
	free_data_map_arr(data, (void ***)&data->map_arr);
	free_data_map_arr(data, (void ***)&data->map_color);
	free_data_map_arr(data, (void ***)&data->is_color_reserved);
	free_data_map_arr(data, (void ***)&data->proj_arr);
	free_data_map_arr(data, (void ***)&data->proj_points);
	free_plane(&data->pl);
	data->esc_cnt = 0;
	data->map_err = 0;
	if (NULL != data->mlx_ptr)
		finish_display(&data->mlx_ptr);
	if (1 == data->malloc_option)
		free(data);
}

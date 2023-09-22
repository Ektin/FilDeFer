/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:18:34 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/22 17:29:39 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_event_mode(int keycode)
{
	if (XK_Right == keycode)
		return (2);
	else if (XK_Left == keycode)
		return (3);
	else if (XK_Up == keycode)
		return (4);
	else if (XK_Down == keycode)
		return (5);
	else if ('i' == keycode)
		return (6);
	else if ('o' == keycode)
		return (7);
	else if ('a' == keycode)
		return (10);
	else if ('d' == keycode)
		return (11);
	else if ('w' == keycode)
		return (12);
	else if ('s' == keycode)
		return (13);
	else if ('c' == keycode)
		return (14);
	return (-1);
}

void	do_if_left_or_right_or_zoom_pressed(int keycode, t_data *data)
{
	if (0 == data->fix_k && ('i' == keycode || 'o' == keycode))
		do_if_k_pressed(data);
	if (XK_Right == keycode || XK_Left == keycode || \
	XK_Up == keycode || XK_Down == keycode || 'i' == keycode || 'o' == keycode)
	{
		reset_image(data);
		plot_projected_points(data, get_event_mode(keycode));
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
			data->img_ptr, 0, 0);
	}
}

void	do_if_adwsc_pressed(int keycode, t_data *data)
{
	if (0 == data->fix_k && 'c' != keycode)
		do_if_k_pressed(data);
	if ('c' == keycode && 0 == data->shift_x && 0 == data->shift_y)
		return ;
	reset_image(data);
	if ('a' == keycode)
		plot_projected_points(data, get_event_mode('a'));
	else if ('d' == keycode)
		plot_projected_points(data, get_event_mode('d'));
	else if ('w' == keycode)
		plot_projected_points(data, get_event_mode('w'));
	else if ('s' == keycode)
		plot_projected_points(data, get_event_mode('s'));
	else if ('c' == keycode)
		plot_projected_points(data, get_event_mode('c'));
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
		data->img_ptr, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:18:34 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/22 17:28:18 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	doifnothing(void *param)
{
	(void) param;
	return (0);
}

int	doifpress(int keycode, t_data *data)
{
	ft_printf("You just pressed %d key\n\n", keycode);
	if (XK_Escape == keycode)
	{
		++data->esc_cnt;
		ft_printf("Escape symbol was pressed %d times\n\n", data->esc_cnt);
		if (1 == data->esc_cnt)
			mlx_loop_end(data->mlx_ptr);
	}
	if (3 == data->busy)
	{
		ft_printf("I am very busy right now, so will ignore ");
		ft_printf("that command. Try again later\n");
		return (1);
	}
	else if (XK_Right == keycode || XK_Left == keycode || \
	XK_Up == keycode || XK_Down == keycode || 'i' == keycode || 'o' == keycode)
		do_if_left_or_right_or_zoom_pressed(keycode, data);
	else if ('a' == keycode || 'd' == keycode || \
		'w' == keycode || 's' == keycode || 'c' == keycode)
		do_if_adwsc_pressed(keycode, data);
	else if ('k' == keycode || 'v' == keycode || \
			'b' == keycode)
		do_if_mode_kvb_pressed(keycode, data);
	return (0);
}

int	do_if_mode_kvb_pressed(int keycode, t_data *data)
{
	if ('k' == keycode)
		do_if_k_pressed(data);
	else if ('v' == keycode)
		do_if_verbatim_pressed(data);
	else if ('b' == keycode)
		do_if_busy_pressed(data);
	return (0);
}

int	doifmouse(int x, int y, int z, t_data *data)
{
	ft_printf("\n\nHi mouse [%d] [%d] [%d]\n\n", x, y, z);
	(void)data;
	return (0);
}

int	doifmouseexit(t_data *data)
{
	++data->destroy_cnt;
	ft_printf("Destroy button was clicked %d times\n\n", data->destroy_cnt);
	if (1 == data->destroy_cnt)
		mlx_loop_end(data->mlx_ptr);
	return (0);
}

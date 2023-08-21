/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:18:34 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/18 20:36:21 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	doifnothing(void *param)
{
	(void) param;
	return (0);
}

int	doifesc(int keycode, t_data *data)
{
	ft_printf("You just pressed %d key\n\n", keycode);
	if (XK_Escape == keycode)
	{
		++data->esc_cnt;
		ft_printf("Escape symbol was pressed %d times\n\n", data->esc_cnt);
		if (2 == data->esc_cnt)
			mlx_loop_end(data->mlx_ptr);
	}
	return (0);
}

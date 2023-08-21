/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:09:17 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/18 22:36:14 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	color_point(int x, int y, int color, t_data *data)
{
	*(int *)(data->img_data + data->size_line * y + \
		data->bits_per_pixel / 8 * x) = color;
	return (0);
}

int	write_error(void)
{
	ft_printf("\n\n\nTHERE IS AN UNEXPECTED CASE HAPPENED IN DRAW_LINE\n\n\n");
	return (1);
}

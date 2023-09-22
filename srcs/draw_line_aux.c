/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:09:17 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/20 19:01:50 by Ektin Op Urims   ###   ########.fr       */
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

int	print_error_after_adjustment(t_point_2d const *point1, \
		t_point_2d const *point2, t_point_2d const *p1, t_point_2d const *p2)
{
	ft_printf("\n\n\033[31mERROR\n");
	ft_printf("I don't understand it happened, but after adjustment you ");
	ft_printf("gave me a point outside the board. Please go and check");
	ft_printf("\nOrig: (%d,%d)--(%d,%d)\n", point1->x, point1->y, \
		point2->x, point2->y);
	ft_printf("\nAdju: (%d, %d) -- (%d, %d)\n", p1->x, p1->y, p2->x, p2->y);
	return (1);
}

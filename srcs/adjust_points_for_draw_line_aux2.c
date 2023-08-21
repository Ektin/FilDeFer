/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_points_for_draw_line_aux2.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:09:17 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/18 22:34:02 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int x)
{
	if (x >= 0)
		return (x);
	if (x == -x)
	{
		ft_printf("\n\nCalling abs for the smallest integer");
		ft_printf(" does not make much sense\n\n");
	}
	return (-x);
}

void	swap(void **ptr1, void **ptr2)
{
	void		*tmp;
	t_point_2d	*p1;
	t_point_2d	*p2;

	p1 = *ptr1;
	p2 = *ptr2;
	ft_printf("\n\nBEGINNING OF SWAP\n\n");
	ft_printf("Before: (%3d,%3d) -- (%3d,%3d)\n\n", p1->x, p1->y, p2->x, p2->y);
	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
	ft_printf("\n\nEND OF SWAP\n\n");
}

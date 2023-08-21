/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_points_for_draw_line_aux1.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:09:17 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/18 22:30:44 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_point_inside(t_point_2d const *p, t_data *data)
{
	if (0 <= p->x && p->x < data->width && \
		0 <= p->y && p->y < data->height)
		return (1);
	return (0);
}

int	does_line_intersect(t_point_2d const *p1, t_point_2d const *p2, \
							t_data *data)
{
	int		q;
	double	k;

	if (is_point_inside(p1, data) || is_point_inside(p2, data))
	{
		ft_printf("\n\nTHE WAS NO NEED TO CALL does_line_intersect\n\n");
		return (0);
	}
	if (p1->x == p2->x)
		return (0);
	k = (double)(p2->y - p1->y) / (p2->x - p1->x); 
	q = 0;
	if (get_side_of_line(0, 0, k, p1) > 0)
		++q;
	if (get_side_of_line(data->width, 0, k, p1) > 0)
		++q;
	if (get_side_of_line(0, data->height, k, p1) > 0)
		++q;
	if (get_side_of_line(data->width, data->height, k, p1) > 0)
		++q;
	if (0 == q || 4 == q)
		return (0);
	return (1);
}

double	get_side_of_line(int x, int y, double k, t_point_2d const *p1)
{
	double	res;

	res = (x - p1->x) * k - (y - p1->y);
	printf("\n\nres [%f]\n\n", res);
	return (res);
}

int	ft_round(double n)
{
	int	res;

	res = (int) n;
	if (n >= 0)
	{
		if (n - res >= res + 1 - n)
			++res;
	}
	if (n < 0)
	{
		if (res - n > n - res + 1)
			--res;
	}
	return (res);
}

void	resizeapointifneeded(t_point_2d *p1)
{
	if ((p1->x << 1) >> 1 != p1->x || (p1->y << 1) >> 1 != p1->y)
	{
		ft_printf("\n\nOh, I see, you give me very large points\n\n");
		ft_printf("\nNon che problema, I will resize it\n\n");
		p1->x >>= 1;
		p1->y >>= 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_points_for_draw_line.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:09:17 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/20 19:02:45 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	adjust_points_for_draw_line(t_point_2d *p1, t_point_2d *p2, t_data *data)
{
	if (is_point_inside(p1, data) && is_point_inside(p2, data))
	{
		return (0);
	}
	resizeapointifneeded(p1);
	resizeapointifneeded(p2);
	if (is_point_inside(p1, data))
	{
		if (p2->x >= data->width || p2->x < 0)
		{
			return (doif_p2x_outofrange(p1, p2, data));
		}
		if (p2->y >= data->height || p2->y < 0)
		{
			return (doif_p2y_outofrange(p1, p2, data));
		}
		else
			ft_printf("\n\nNOTHING ELSE IS POSSIBLE\n\n");
	}
	if (is_point_inside(p2, data))
	{
		adjust_points_for_draw_line(p2, p1, data);
		return (0);
	}
	return (doif_bothpoints_outofrange(p1, p2, data));
}

int	doif_p2x_outofrange(t_point_2d *p1, t_point_2d *p2, t_data *data)
{
	double	k;

	if (p2->x == p1->x)
		return (1);
	if (p2->x >= data->width)
	{
		k = ((double)(p2->y - p1->y) / (p2->x - p1->x));
		p2->x = data->width - 1;
		p2->y = p1->y + ft_round((p2->x - p1->x) * k);
		adjust_points_for_draw_line(p1, p2, data);
		return (0);
	}
	if (p2->x < 0)
	{
		k = ((double)(p2->y - p1->y) / (p2->x - p1->x));
		p2->x = 0;
		p2->y = p1->y + ft_round((p2->x - p1->x) * k);
		adjust_points_for_draw_line(p1, p2, data);
		return (0);
	}
	return (1);
}

int	doif_p2y_outofrange(t_point_2d *p1, t_point_2d *p2, t_data *data)
{
	double	k;

	if (p2->y == p1->y)
		return (1);
	if (p2->y >= data->height)
	{
		k = ((double)(p2->x - p1->x) / (p2->y - p1->y));
		p2->y = data->height - 1;
		p2->x = p1->x + ft_round((p2->y - p1->y) * k);
		return (0);
	}
	if (p2->y < 0)
	{
		k = ((double)(p2->x - p1->x) / (p2->y - p1->y));
		p2->y = 0;
		p2->x = p1->x + ft_round((p2->y - p1->y) * k);
		return (0);
	}
	return (1);
}

int	doif_bothpoints_outofrange(t_point_2d *p1, t_point_2d *p2, t_data *data)
{
	if (0 == does_segment_intersect(p1, p2, data))
	{
		return (1);
	}
	doif_p2x_outofrange(p1, p2, data);
	doif_p2y_outofrange(p1, p2, data);
	adjust_points_for_draw_line(p2, p1, data);
	return (0);
}

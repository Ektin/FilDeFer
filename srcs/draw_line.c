/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:09:17 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/20 18:58:56 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* here is definitely a problem with the norminette, it wants
	- dx >= -dy
	so with space on the left-hand side, 
	and without space in the right-hand side
*/
int	draw_line(t_point_2d const *point1, t_point_2d const *point2, \
				int color, t_data *data)
{
	int			dx;
	int			dy;
	t_point_2d	p1;
	t_point_2d	p2;

	set_point_2d(&p1, point1);
	set_point_2d(&p2, point2);
	if (1 == adjust_points_for_draw_line(&p1, &p2, data))
		return (1);
	if (0 == is_point_inside(&p1, data) || 0 == is_point_inside(&p2, data))
		return (print_error_after_adjustment(point1, point2, &p1, &p2));
	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (dx > 0 && dy >= 0 && dy <= dx)
		draw_line_dx_part1(&p1, &p2, color, data);
	else if (dx > 0 && dy < 0 && 0 <= dx + dy)
		draw_line_dx_part2(&p1, &p2, color, data);
	else if (dy > 0 && dx >= 0 && dx < dy)
		draw_line_dy_part1(&p1, &p2, color, data);
	else if (dy > 0 && dx < 0 && 0 < dx + dy)
		draw_line_dy_part2(&p1, &p2, color, data);
	else if ((dx < 0 && - dx >= dy && - dx >= -dy) \
		|| (dy < 0 && - dy > dx && - dy > -dx))
		draw_line(&p2, &p1, color, data);
	return (0);
}

/*ft_printf("\n\ndraw_line_dy_part2 [%d]", color);
ft_printf("(%3d, %3d) -- (%3d, %3d)\n\n", 
			p1->x, p1->y, p2->x, p2->y);
*/
//if (dx > 0 && dy >= 0 && dy <= dx)
int	draw_line_dx_part1(t_point_2d const *p1, t_point_2d const *p2, \
				int color, t_data *data)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	err;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	if (!(dx > 0 && dy >= 0 && dy <= dx))
		return (write_error());
	x = p1->x;
	y = p1->y;
	err = 0;
	while (x < p2->x)
	{
		color_point(x, y, color, data);
		err += 2 * dy - dx;
		if (err >= 0 && ++y)
			err -= dx;
		else
			err += dx;
		++x;
	}
	color_point(x, y, color, data);
	return (0);
}

// if (dx > 0 && dy < 0 && 0 <= dx + dy)
int	draw_line_dx_part2(t_point_2d const *p1, t_point_2d const *p2, \
				int color, t_data *data)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	err;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	if (!(dx > 0 && dy < 0 && 0 <= dx + dy))
		return (write_error());
	x = p1->x;
	y = p1->y;
	err = 0;
	while (x < p2->x)
	{
		color_point(x, y, color, data);
		err += 2 * dy + dx;
		if (err <= 0 && y--)
			err += dx;
		else
			err -= dx;
		++x;
	}
	color_point(x, y, color, data);
	return (0);
}

//if (dy > 0 && dx >= 0 && dx < dy)
int	draw_line_dy_part1(t_point_2d const *p1, t_point_2d const *p2, \
				int color, t_data *data)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	err;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	if (!(dy > 0 && dx >= 0 && dx < dy))
		return (write_error());
	x = p1->x;
	y = p1->y;
	err = 0;
	while (y < p2->y)
	{
		color_point(x, y, color, data);
		err += 2 * dx - dy;
		if (err >= 0 && ++x)
			err -= dy;
		else
			err += dy;
		++y;
	}
	color_point(x, y, color, data);
	return (0);
}

// if (dy > 0 && dx < 0 && 0 < dx + dy)
int	draw_line_dy_part2(t_point_2d const *p1, t_point_2d const *p2, \
				int color, t_data *data)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	err;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	if (!(dy > 0 && dx < 0 && 0 < dx + dy))
		return (write_error());
	x = p1->x;
	y = p1->y;
	err = 0;
	while (y < p2->y)
	{
		color_point(x, y, color, data);
		err += 2 * dx + dy;
		if (err <= 0 && x--)
			err += dy;
		else
			err -= dy;
		++y;
	}
	color_point(x, y, color, data);
	return (0);
}

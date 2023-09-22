/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isoplane_change_params.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 16:05:01 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/21 23:30:24 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_isoplane(t_isoplane *pl, double deltaphi)
{
	ft_printf("never here\033[33m\n\n");
	ft_printf("deltaphi is [%f]\n\n", deltaphi);
	pl->phi += deltaphi;
	compute_a_b_isoplane(pl);
	set_vector_n(pl);
	pl->n2 = dot(&pl->n, &pl->n);
	compute_ep_eq(pl);
}

void	rotate_right_isoplane(t_isoplane *pl)
{
	ft_printf("\n\nWe are never here, rotate_right_isoplane\n\n");
	rotate_isoplane(pl, pl->deltaphi);
}

void	rotate_left_isoplane(t_isoplane *pl)
{
	ft_printf("\n\nWe are never here, rotate_left_isoplane\n\n");
	rotate_isoplane(pl, -pl->deltaphi);
}

/* pl->a = sqrt(2.0) * cos(pl->phi); pl->b = sqrt(2.0) * sin(pl->phi); */
// how do you feel dividing by zero? or taking tan of pi/2?
void	compute_a_b_isoplane(t_isoplane *pl)
{
	double	t;

	t = tan(pl->psi);
	pl->a = t * pl->c / sin(pl->phi);
	pl->b = t * pl->c / cos(pl->phi);
}

void	reset_image(t_data *data)
{
	ft_memset(data->img_data, 0, data->bits_per_pixel / 8 * \
		data->width * data->height);
}

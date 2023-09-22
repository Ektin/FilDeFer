/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isoplane_setting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:52:37 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/22 17:40:42 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* mode:
	1: initial
	2: rotate right
	3: rotate left
*/
int	init_isoplane(t_isoplane **pl, int mode)
{
	if (1 == mode)
	{
		*pl = (t_isoplane *)malloc(sizeof(t_isoplane));
		if (NULL == *pl)
			return (malloc_err("init_isoplane"));
		(*pl)->deltaphi = 0.01;
		(*pl)->phi = M_PI / 4;
		(*pl)->phi = M_PI / 3;
		(*pl)->psi = M_PI / 2.1;
		(*pl)->psi = acos(2.0 / 3.0);
		(*pl)->c = 10.0;
	}
	else if (get_event_mode(XK_Right) == mode)
		(*pl)->phi += (*pl)->deltaphi;
	else if (get_event_mode(XK_Left) == mode)
		(*pl)->phi -= (*pl)->deltaphi;
	else if (get_event_mode(XK_Up) == mode)
		(*pl)->psi += (*pl)->deltaphi;
	else if (get_event_mode(XK_Down) == mode)
		(*pl)->psi -= (*pl)->deltaphi;
	adjust_angles(&((*pl)->phi), &((*pl)->psi));
	compute_a_b_isoplane(*pl);
	set_vector_n(*pl);
	compute_ep_eq(*pl);
	return (0);
}

void	set_vector_n(t_isoplane *pl)
{
	double	a1;
	double	b1;
	double	c1;

	a1 = ft_abs(pl->a);
	b1 = ft_abs(pl->b);
	c1 = ft_abs(pl->c);
	if (a1 <= b1 && a1 <= c1 && b1 != 0 && c1 != 0)
		setvec_xyz(&pl->n, 1, pl->a / pl->b, pl->a / pl->c);
	else if (b1 <= a1 && b1 <= c1 && a1 != 0 && c1 != 0)
		setvec_xyz(&pl->n, pl->b / pl->a, 1, pl->b / pl->c);
	else if (c1 <= a1 && c1 <= b1 && a1 != 0 && b1 != 0)
		setvec_xyz(&pl->n, pl->c / pl->a, pl->c / pl->b, 1);
	else
	{
		ft_printf("\n\nSomething is really wrong in set_vector_n, ");
		ft_printf("[%f][%f][%f]\n\n", pl->a, pl->b, pl->c);
	}
	if (1 == 0)
		setvec_xyz(&pl->n, 1.0 / pl->a, 1.0 / pl->b, 1.0 / pl->c);
	pl->n2 = dot(&pl->n, &pl->n);
}

/*if (dnum1 > dnum2)
	{
		setvec_xyz(&pl->ep, 1, -pl->b / pl->a, 0);
	}
	else if (dnum2 > dnum1)
	{
		setvec_xyz(&pl->ep, -pl->a / pl->b, 1, 0);
	}
	*/
	/*if ((pl->a >= 0 && pl->b >= 0) || (pl->a < 0 && pl->b < 0))
		setvec_xyz(&pl->ep, pl->a, -pl->b, 0);
	else
		setvec_xyz(&pl->ep, -pl->a, pl->b, 0);
*/
void	compute_ep_eq(t_isoplane *pl)
{
	double	dnum1;
	double	dnum2;

	pl->e.x = pl->a / 3.0;
	pl->e.y = pl->b / 3.0;
	pl->e.z = pl->c / 3.0;
	pl->e.k = 1.0;
	dnum1 = ft_abs(pl->a);
	dnum2 = ft_abs(pl->b);
	setvec_xyz(&pl->ep, cos(pl->phi), -sin(pl->phi), 0);
	pl->ep1 = sqrt(dot(&pl->ep, &pl->ep));
	if (ft_abs(pl->a) >= ft_abs(pl->b) && pl->a != 0)
	{
		dnum1 = 1.0 / (1.0 + (pl->b / pl->a) * (pl->b / pl->a));
		setvec_xyz(&pl->eq, pl->b / pl->a * pl->b * dnum1, \
						pl->b * dnum1, -pl->c);
	}
	else if (ft_abs(pl->a) < ft_abs(pl->b))
	{
		dnum1 = pl->a / pl->b;
		dnum2 = 1.0 / (1.0 + dnum1 * dnum1);
		setvec_xyz(&pl->eq, pl->a * dnum2, pl->a * dnum1 * dnum2, -pl->c);
	}
	pl->eq1 = sqrt(dot(&pl->eq, &pl->eq));
	set_oe_n_dot(pl);
}

void	set_oe_n_dot(t_isoplane *pl)
{
	pl->endot = dot(&pl->e, &pl->n);
}

/*void	compute_p_q(t_isoplane *pl)
{
	double	rt;

	pl->p.z = pl->c / 3.0;
	pl->p.x = pl->a * 4.0 / 3.0;
	pl->p.y = pl->b * 2.0 / 3.0 - pl->p.x * pl->b / pl->a;
	pl->q.z = pl->c * (-2.0) / 3.0;
	if (ft_abs(pl->a) >= ft_abs(pl->b) && ft_abs(pl->b) > 0)
	{
		rt = pl->b / pl->a * pl->b / pl->a;
		pl->q.x = (1.0 + 2.0 * rt) / 3.0 - pl->q.z / pl->c * rt;
		pl->q.x *= pl->a / (1.0 + rt);
		pl->q.y = (2.0 + rt) / 3.0 - pl->q.z / pl->c;
		pl->q.y *= pl->b / (1.0 + rt);
	}
	else if (ft_abs(pl->a) < ft_abs(pl->b) && ft_abs(pl->a) > 0)
	{
		rt = pl->a / pl->b;
		rt *= rt;
		pl->q.x = (rt + 2.0) / 3.0 - pl->q.z / pl->c;
		pl->q.x *= pl->a / (1.0 + rt);
		pl->q.y = (2.0 * rt + 1.0) / 3.0 - rt * pl->q.z / pl->c;
		pl->q.y *= pl->b / (1.0 + rt);
	}
	else
		ft_printf("Nothing else is possible");
}*/

void	free_plane(t_isoplane **pl)
{
	free(*pl);
	*pl = NULL;
}

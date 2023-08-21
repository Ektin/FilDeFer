/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isoplane_setting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:52:37 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/21 20:04:41 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_isoplane(t_isoplane **pl)
{
	*pl = (t_isoplane *)malloc(sizeof(t_isoplane));
	if (NULL == *pl)
		return (malloc_err("init_isoplane"));
	(*pl)->a = 1.0;
	(*pl)->b = 1.0;
	(*pl)->c = 1.0;
	setvec_xyz(&(*pl)->n, 1.0 / (*pl)->a, 1.0 / (*pl)->b, 1.0 / (*pl)->c);
	(*pl)->n2 = dot(&(*pl)->n, &(*pl)->n);
	compute_ep_eq(*pl);
	compute_p_q(*pl);
	return (0);
}

void	compute_ep_eq(t_isoplane *pl)
{
	double	dnum;

	setvec_xyz(&pl->ep, pl->a, -pl->b, 0);
	pl->ep2 = dot(&pl->ep, &pl->ep);
	dnum = 1.0 / (pl->a / pl->b + pl->b / pl->a);
	setvec_xyz(&pl->eq, pl->b * dnum, pl->a * dnum, -pl->c);
	pl->eq2 = dot(&pl->eq, &pl->eq);
	pl->e.x = pl->a / 3.0;
	pl->e.y = pl->b / 3.0;
	pl->e.z = pl->c / 3.0;
}

void	compute_p_q(t_isoplane *pl)
{
	double	rt;

	pl->p.z = pl->c / 3.0;
	pl->p.x = pl->a * 4.0 / 3.0;
	pl->p.y = pl->b * 2.0 / 3.0 - pl->p.x * pl->b / pl->a;
	pl->q.z = pl->c * (-2.0) / 3.0;
	if (pl->a >= pl->b && pl->b > 0)
	{
		rt = pl->b / pl->a * pl->b / pl->a;
		pl->q.x = (1.0 + 2.0 * rt) / 3.0 - pl->q.z / pl->c * rt;
		pl->q.x *= pl->a / (1.0 + rt);
		pl->q.y = (2.0 + rt) / 3.0 - pl->q.z / pl->c;
		pl->q.y *= pl->b / (1.0 + rt);
	}
	else if (pl->a < pl->b && pl->a > 0)
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
}

void	free_plane(t_isoplane **pl)
{
	free(*pl);
	*pl = NULL;
}

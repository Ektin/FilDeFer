/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:57:45 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/22 17:45:19 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	normalize_max_vec(t_vec *v)
{
	double	a1;
	double	b1;
	double	c1;
	double	k;

	a1 = ft_abs(v->x);
	b1 = ft_abs(v->y);
	c1 = ft_abs(v->z);
	if (a1 >= b1 && a1 >= c1 && a1 != 0)
		k = 1.0 / a1;
	else if (b1 >= a1 && b1 >= c1 && b1 != 0)
		k = 1.0 / b1;
	else if (c1 >= a1 && c1 >= b1 && c1 != 0)
		k = 1.0 / c1;
	*v = prod(k, *v);
}

/* normlization is done in 2 steps: 
	normalize_max, 
	then use ft_sqrt, it will be used with a number between 1 and 3
	divide by norm
*/
void	normalize_vec(t_vec *v)
{
	double	k;

	normalize_max_vec(v);
	k = v->x * v->x + v->y * v->y + v->z * v->z;
	k = ft_sqrt(k);
	k = 1.0 / k;
	*v = prod(k, *v);
}

// should be used with 1 <= a <= 3, otherwise use official sqrt
double	ft_sqrt(double a)
{
	double	res;
	int		i;

	if (!(0.1 <= a && a <= 10.0))
	{
		ft_printf("%sUnauthorised usage of ft_sqrt: [%f]\n", a, RED);
		return (sqrt(a));
	}
	res = 1;
	i = -1;
	while (++i < 6)
	{
		res = (res + (a / res)) / 2.0;
	}
	return (res);
}

void	adjust_angles(double *phi, double *psi)
{
	if (*phi > M_PI)
		*phi -= 2 * M_PI;
	else if (*phi < -M_PI)
		*phi += 2 * M_PI;
	if (*psi >= M_PI / 2.01)
		*psi = M_PI / 2.01;
	else if (*psi <= -M_PI / 2.01)
		*psi = -M_PI / 2.01;
}

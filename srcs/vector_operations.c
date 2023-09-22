/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:45:29 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/20 20:15:39 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec	prod(double k, t_vec vec)
{
	t_vec	res;

	setvec_xyz(&res, k * vec.x, k * vec.y, k * vec.z);
	return (res);
}

t_vec	add(t_vec v1, t_vec v2)
{
	t_vec	res;

	setvec_xyz(&res, v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	return (res);
}

t_vec	diff(t_vec v1, t_vec v2)
{
	t_vec	res;

	setvec_xyz(&res, v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	return (res);
}

double	dot(t_vec const *v1, t_vec const *v2)
{
	return ((v1->x * v2->x + v1->y * v2->y + v1->z * v2->z) * v1->k * v2->k);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:45:29 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/15 13:31:31 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	setvec2(t_vec2 *vec2, double x, double y)
{
	vec2->x = x;
	vec2->y = y;
}

void	setvec_xyz(t_vec *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
	vec->k = 1.0;
}

void	setvec_k(t_vec *vec, double k)
{
	vec->k = k;
}

void	setvec_vec(t_vec *vec, t_vec const *src)
{
	vec->x = src->x;
	vec->y = src->y;
	vec->z = src->z;
	vec->k = src->k;
}

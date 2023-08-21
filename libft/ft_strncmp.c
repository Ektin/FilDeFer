/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:43:25 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/01/29 23:46:35 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, t_size_t n)
{
	t_size_t	index;
	int			res;

	res = 0;
	index = 0;
	while (*str1 && *str2 && index < n)
	{
		res = *str1 - *str2;
		if (*str1 == *str2)
		{
			++str1;
			++str2;
			++index;
		}
		else
		{
			return ((unsigned char)*str1 - (unsigned int)*str2);
		}
	}
	if (index == n)
		return (res);
	return ((unsigned char)*str1 - (unsigned int)*str2);
}

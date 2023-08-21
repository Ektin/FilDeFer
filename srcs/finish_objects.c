/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:10:35 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/13 16:33:43 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	finish_image(void *mlx_ptr, void **img_ptr)
{
	if (NULL == mlx_ptr || NULL == img_ptr || NULL == *img_ptr)
	{
		ft_printf("\n\nWRONG CALL OF finish_image\n\n");
		return (1);
	}
	mlx_destroy_image(mlx_ptr, *img_ptr);
	*img_ptr = NULL;
	return (0);
}

int	finish_window(void *mlx_ptr, void **win_ptr)
{
	if (NULL == mlx_ptr || NULL == win_ptr || NULL == *win_ptr)
	{
		ft_printf("\n\nWRONG CALL OF finish_window\n\n");
		return (1);
	}
	mlx_destroy_window(mlx_ptr, *win_ptr);
	*win_ptr = NULL;
	return (0);
}

int	finish_display(void **mlx_ptr)
{
	if (NULL == mlx_ptr || NULL == *mlx_ptr)
	{
		ft_printf("\n\nWRONG CALL OF finish_display\n\n");
		return (1);
	}
	mlx_destroy_display(*mlx_ptr);
	free(*mlx_ptr);
	*mlx_ptr = NULL;
	return (0);
}

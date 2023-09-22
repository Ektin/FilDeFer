/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:15:52 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/22 11:26:06 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	\
	to exit the mlx_loop(mlx_ptr),\
	you either
	a) call mlx_loop_end(mlx_ptr) in your function that treats escape, or
	b) register mlx_loop_hook(mlx_ptr, donothing, NULL) before mlx_loop,
	c) you can do both.
	I do not understand how it works.
	I do not understand how the parameter int keysymb is passed to doifesc.
	You cannot free the mlx_ptr when escaping, you need to do that later, 
	after the mlx_loop(mlx_ptr) is finished.
	14 Aug 2023
	***
	To see the list of all keys, go to /usr/include/X11/keysymdef.h
	By the way, another strange thing is that it is not enough to include 
	<X11/keysymdef.h>, instead we need to include <X11/keysymdef.h>, which
	includes <X11/keysymdef.h> in it
	/usr/include/X11/X.h also contains important constants
	22 Sep 2023
*/

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	int		fd;

	if (0 != read_data(argc, argv, &data, &fd))
		return (1);
	if (1 == 0)
		print_data_map_arr(&data);
	plot_projected_points(&data, 1);
	if (1 == 0)
	{
		clear_data(&data);
		close(fd);
		return (0);
	}
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_hook(data.win_ptr, 0, 0, doifnothing, NULL);
	mlx_loop_hook(data.mlx_ptr, doifnothing, NULL);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, doifpress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, 0, doifmouseexit, &data);
	mlx_loop(data.mlx_ptr);
	clear_data(&data);
	close(fd);
	return (0);
}
/* mlx_hook(data.win_ptr, ButtonRelease, ButtonReleaseMask, doifmouse, &data);
mlx_mouse_hook(data.win_ptr, doifmouse, &data); */

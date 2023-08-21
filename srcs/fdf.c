/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:15:52 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/21 20:31:45 by Ektin Op Urims   ###   ########.fr       */
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
	plot_projected_points(&data);
	if (1 == 0)
	{
		clear_data(&data);
		close(fd);
		return (0);
	}
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
	mlx_hook(data.win_ptr, 0, 0, doifnothing, NULL);
	mlx_loop_hook(data.mlx_ptr, doifnothing, NULL);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, doifesc, &data);
	mlx_loop(data.mlx_ptr);
	clear_data(&data);
	close(fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:11:17 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/21 18:20:32 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	malloc_err(char const *str)
{
	ft_printf("\n\nMALLOC EROR IN [%s]\n\n", str);
	return (1);
}

int	set_fd(int argc, char **argv, int *fd)
{
	if (argc >= 3)
		return (-1);
	if (2 == argc)
		*fd = open(argv[1], O_RDONLY);
	if (1 == argc)
		*fd = open("test_maps/42.fdf", O_RDONLY);
	if (-1 == *fd)
	{
		ft_printf("\n\nError reading map\n\n");
		return (-1);
	}
	return (0);
}

int	read_input_init_data(int argc, char **argv, t_data *data, int *fd)
{
	int	width;
	int	height;

	if (-1 == set_fd(argc, argv, fd))
		return (1);
	width = 1000;
	height = 1000;
	init_data(data, 0);
	if (1 == create_data(data, width, height))
	{
		close(*fd);
		return (1);
	}
	return (0);
}

int	read_data_set_ncol_nrow(int argc, char **argv, t_data *data, int *fd)
{
	char	*str;
	int		j;

	if (0 != read_input_init_data(argc, argv, data, fd))
		return (1);
	str = get_next_line(*fd);
	data->ncol = 0;
	data->nrow = 0;
	while (NULL != str)
	{
		++data->nrow;
		j = ft_wc(str, ' ');
		if (0 == data->ncol)
			data->ncol = j;
		else if (0 != data->ncol && data->ncol != j)
		{
			ft_printf("\n\nTHE MAP IS CORRUPTED\n[%d][%d][%d]\n", \
					data->nrow, j, data->ncol);
			data->map_err = 1;
		}
		free(str);
		str = get_next_line(*fd);
	}
	close(*fd);
	return (0);
}

int	allocate_arr(t_data *data, void ***arr, int size)
{
	int	i;
	int	tutto_bene;

	tutto_bene = 1;
	*arr = (void **)malloc(sizeof(void *) * data->nrow);
	if (NULL == *arr)
		return (malloc_err("read_data_allocate_arr, void**"));
	i = 0;
	while (i < data->nrow && 1 == tutto_bene)
	{
		(*arr)[i] = (void *)malloc(size * data->ncol);
		if (NULL == (*arr)[i])
		{
			tutto_bene = 0;
			free_data_map_arr(data, arr);
			return (malloc_err("read_data_allocate_arr, void*"));
		}
		++i;
	}
	return (0);
}

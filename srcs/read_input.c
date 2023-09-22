/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 13:11:17 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/08/23 16:27:57 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	free_data_map_arr(t_data *data, void ***arr)
{
	int	i;

	if (NULL == data || NULL == arr || NULL == *arr)
		return (0);
	i = 0;
	while (i < data->nrow)
	{
		if (NULL != (*arr)[i])
		{
			free((*arr)[i]);
			(*arr)[i] = NULL;
			++i;
		}
	}
	free(*arr);
	*arr = NULL;
	return (0);
}

int	read_data_allocate_all_arrays(t_data *data)
{
	if (allocate_arr(data, (void ***)(&data->map_arr), sizeof(int)))
		return (1);
	if (allocate_arr(data, (void ***)(&data->map_color), sizeof(int)))
		return (1);
	if (allocate_arr(data, (void ***)(&data->is_color_reserved), \
								sizeof(char)))
		return (1);
	if (allocate_arr(data, (void ***)&data->proj_arr, sizeof(t_vec2)))
		return (1);
	if (allocate_arr(data, \
		(void ***)&data->proj_points, sizeof(**data->proj_points)))
		return (1);
	return (0);
}

int	read_data(int argc, char **argv, t_data *data, int *fd)
{
	char	*str;
	char	**arr_str;
	int		j;
	int		i;

	if (0 != read_data_set_ncol_nrow(argc, argv, data, fd))
		return (1);
	if (0 != set_fd(argc, argv, fd) || 1 == data->map_err)
		return (1);
	if (1 == read_data_allocate_all_arrays(data))
		return (1);
	str = get_next_line(*fd);
	i = -1;
	while (NULL != str)
	{
		++i;
		arr_str = ft_split(str, ' ');
		j = -1;
		while (NULL != arr_str[++j])
			treat_num_color(arr_str[j], i, j, data);
		free_split(arr_str);
		free(str);
		str = get_next_line(*fd);
	}
	return (0);
}

void	treat_num_color(char const *num_comma_color, int i, int j, t_data *data)
{
	char	**num_color;

	data->map_arr[i][j] = ft_atoi(num_comma_color);
	num_color = ft_split(num_comma_color, ',');
	if (NULL != num_color && NULL != num_color[1])
	{
		data->map_color[i][j] = ft_atoi_0x(num_color[1]);
		data->is_color_reserved[i][j] = 1;
	}
	else
	{
		data->map_color[i][j] = 0xffffff;
		data->is_color_reserved[i][j] = 0;
	}
	free_split(num_color);
}

void	print_data_map_arr(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	ft_printf("\nThe map is of the size [%d]x[%d]\n", data->nrow, data->ncol);
	if (0 == 1)
		return ;
	while (++i < data->nrow)
	{
		j = 0;
		ft_printf("\033[33m%3d \033[0m", i + 1);
		while (j < data->ncol)
		{
			ft_printf("%2d", data->map_arr[i][j]);
			if (1 == data->is_color_reserved[i][j])
			{
				ft_printf(",");
				ft_printf("%#x ", data->map_color[i][j]);
			}
			else
				ft_printf(" ");
			++j;
		}
		ft_printf("\n");
	}
}

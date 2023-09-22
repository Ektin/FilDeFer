/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:18:34 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/09/22 16:44:46 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	do_if_k_pressed(t_data *data)
{
	data->fix_k ^= 1;
	ft_printf("\nfix_k is ");
	if (1 == data->fix_k)
	{
		ft_printf("ON: proportion will not change as ");
		ft_printf("image being rotated\n");
	}
	else
		ft_printf("OFF: image will be adjusted to fit in window\n");
}

void	do_if_verbatim_pressed(t_data *data)
{
	data->verbatim ^= 1;
	ft_printf("\noption verbatim is ", data->verbatim);
	if (1 == data->verbatim)
	{
		ft_printf("ON: you will receive all information about image\n");
		ft_printf("If not already done so, ");
		ft_printf("for a better experience,\n  - include <stdio.h> in ");
		ft_printf("'fdf.h' and\n  - change ft_printf to printf for %%f in ");
		ft_printf("print_details_isoplane, isoplane_computing_part3.c");
		ft_printf("\n  - and in rotate_isoplane, isoplane_change_params.c");
		ft_printf("\n");
	}
	else
		ft_printf("OFF: no information will be printed regarding the image\n");
}

void	do_if_busy_pressed(t_data *data)
{
	data->busy ^= 2;
	ft_printf("\nIgnore this option, for it to work one needs ");
	ft_printf("parallel proccesses\noption busy is ", data->verbatim);
	if (1 == (data->busy >> 1))
	{
		ft_printf("ON: we will ignore all command until ");
		ft_printf("we are done with previous task\n");
	}
	else
	{
		ft_printf("OFF: we will do every command, even if ");
		ft_printf("we are not done with previous yet\n");
	}
}

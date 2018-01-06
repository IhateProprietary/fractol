/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 03:13:18 by jye               #+#    #+#             */
/*   Updated: 2018/01/06 04:35:15 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"

#include <stddef.h>

int		init_mlx_win(t_mlx *mlx)
{
	if ((mlx->ptr = mlx_init()) == 0)
	{
		return (1);
	}
	if ((mlx->win = mlx_new_window(mlx->ptr, IMAGEWIDTH,
			IMAGEHEIGHT, PROGRAM_NAME)) == 0)
	{
		return (1);
	}
	return (0);
}

int		init_mlx_img(t_mlx *mlx)
{
	int dummy;

	if ((mlx->img = mlx_new_image(mlx->ptr, IMAGEWIDTH, IMAGEHEIGHT)) == 0)
	{
		return (1);
	}
	mlx->img__ = mlx_get_data_addr(mlx->img, &dummy, &mlx->img_size, &dummy);
	return (0);
}

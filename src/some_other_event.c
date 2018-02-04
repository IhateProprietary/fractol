/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_other_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 07:57:22 by jye               #+#    #+#             */
/*   Updated: 2018/02/04 08:09:32 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mlx_mousek_hook(int key, int x, int y, void *param)
{
	(void)x;
	(void)y;
	if (key == 7)
		mlx_zoomopin_event(param);
	else if (key == 6)
		mlx_zoomopout_event(param);
	mlx_refresh_image(*((void **)param), *((void **)param + 1));
	return (0);
}

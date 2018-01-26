/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ihate_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 04:18:15 by jye               #+#    #+#             */
/*   Updated: 2018/01/17 08:25:03 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mlx_additer_event(void *param)
{
	t_fract *f;

	f = ((t_fract *)*((void **)param + 1));
	if (f->iteration > 2000)
		return ;
	f->iteration += 10;
}

void	mlx_subiter_event(void *param)
{
	t_fract *f;

	f = ((t_fract *)*((void **)param + 1));
	if (f->iteration == 10)
		return ;
	f->iteration -= 10;
}

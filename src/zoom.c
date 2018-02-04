/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 03:28:56 by jye               #+#    #+#             */
/*   Updated: 2018/02/04 08:08:10 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define ZOOM_VALUE 1.1

void	mlx_zoomopin_event(void *param)
{
	t_fract *f;
	double	reb;
	double	rea;
	double	imb;
	double	ima;

	f = ((t_fract *)*((void **)param + 1));
	if (f->max_re - f->min_re < 0.000000000001)
		return ;
	reb = f->min_re + f->x * ((f->max_re - f->min_re) / (IMAGEWIDTH));
	imb = f->max_im - f->y * ((f->max_im - f->min_im) / (IMAGEHEIGHT));
	f->min_re /= ZOOM_VALUE;
	f->max_re /= ZOOM_VALUE;
	f->max_im /= ZOOM_VALUE;
	f->min_im /= ZOOM_VALUE;
	rea = f->min_re + f->x * ((f->max_re - f->min_re) / (IMAGEWIDTH));
	ima = f->max_im - f->y * ((f->max_im - f->min_im) / (IMAGEHEIGHT));
	f->min_re += reb - rea;
	f->max_re += reb - rea;
	f->max_im += imb - ima;
	f->min_im += imb - ima;
}

void	mlx_zoomopout_event(void *param)
{
	t_fract *f;
	double	reb;
	double	rea;
	double	imb;
	double	ima;

	f = ((t_fract *)*((void **)param + 1));
	if (f->max_re - f->min_re > 50.0f)
		return ;
	reb = f->min_re + f->x * ((f->max_re - f->min_re) / (IMAGEWIDTH));
	imb = f->max_im - f->y * ((f->max_im - f->min_im) / (IMAGEHEIGHT));
	f->min_re *= ZOOM_VALUE;
	f->max_re *= ZOOM_VALUE;
	f->max_im *= ZOOM_VALUE;
	f->min_im *= ZOOM_VALUE;
	rea = f->min_re + f->x * ((f->max_re - f->min_re) / (IMAGEWIDTH));
	ima = f->max_im - f->y * ((f->max_im - f->min_im) / (IMAGEHEIGHT));
	f->min_re += reb - rea;
	f->max_re += reb - rea;
	f->max_im += imb - ima;
	f->min_im += imb - ima;
}

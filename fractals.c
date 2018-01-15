/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 04:02:59 by jye               #+#    #+#             */
/*   Updated: 2018/01/15 04:47:56 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

const static t_fract	g_nfract[] = {
	(t_fract){
		.x_re = -1.2, .y_im = 0.160, .flags = FRACTAL_IS_JULIA,
		.min_re = -1.75, .max_re = 1.75, .min_im = -1.0, .max_im = 1.0,
		.frac = "julia", .iteration = 300
	},
	(t_fract){
		.x_re = -1.2, .y_im = 0.160, .flags = 0,
		.min_re = -2.25, .max_re = 1.25, .min_im = -1.0, .max_im = 1.0,
		.frac = "mandelbrot", .iteration = 300
	},
	(t_fract){
		.x_re = 3.0, .y_im = 0.160, .flags = FRACTAL_IS_MULTIBROT,
		.min_re = -1.75, .max_re = 1.75, .min_im = -1.0, .max_im = 1.0,
		.frac = "multibrot", .iteration = 100
	}
};

void	mlx_chfractal_event(t_fract *f, int n)
{
	int		csetsize;

	csetsize = f->csetsize;
	*f = g_nfract[n];
	f->csetsize = csetsize;
}

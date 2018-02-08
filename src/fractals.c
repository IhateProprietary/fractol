/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 04:45:57 by jye               #+#    #+#             */
/*   Updated: 2018/02/08 04:22:08 by jye              ###   ########.fr       */
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

int		mlx_chfractal_event(t_fract *f, int n)
{
	t_fract					b;
	static t_fract			nfract[3] = {{N_XD, R_XD, I_XD, NE_XD
		, FRACTAL_IS_MULTIBROT}};

	b = *f;
	if (n >= MAX_FRACTALS)
		return (1);
	*f = nfract[n];
	f->csetsize = b.csetsize;
	f->color = b.color;
	f->set = b.set;
	return (0);
}

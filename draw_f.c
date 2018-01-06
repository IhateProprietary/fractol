/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 00:45:00 by jye               #+#    #+#             */
/*   Updated: 2018/01/06 10:09:37 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stddef.h>

void	runcl_task(const t_mlx *m, cl_uint x, cl_double c[2])
{
	size_t	workdim;

	workdim = IMAGEWIDTH;
	clSetKernelArg(m->cl.kernel, 1, sizeof(cl_double) * 2, c);
	clSetKernelArg(m->cl.kernel, 2, sizeof(cl_uint) * 1, &x);
	clEnqueueNDRangeKernel(m->cl.queue, m->cl.kernel, 1, 0, &workdim, 0, 0, NULL, 0);
}

void	draw_nfract(const t_mlx *m, const t_fract *f, unsigned int n[2])
{
	t_complex		fact;
	t_complex		c;

	fact.re = (f->max_re - f->min_re) / (IMAGEWIDTH);
	fact.im = (f->max_im - f->min_im) / (IMAGEHEIGHT);
	while (n[0] < n[1])
	{
		/* c.im = f->max_im - n[0] * fact.im + f->movey; */
		/* while (x < IMAGEWIDTH) */
		/* { */
		/* c.re = f->min_re + x * fact.re + f->movex; */
		runcl_task(m, n[0], (cl_double[2]){fact.re, fact.im});
		/* 	++x; */
		/* /\* } *\/ */
		/* x = 0; */
		++n[0];
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 00:45:00 by jye               #+#    #+#             */
/*   Updated: 2018/01/08 02:07:04 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stddef.h>

void	runcl_task(const t_mlx *m, cl_uint y, cl_double c[2])
{
	const static size_t	workdim = IMAGEWIDTH;

	clSetKernelArg(m->cl.kernel, 1, sizeof(cl_double) * 2, c);
	clSetKernelArg(m->cl.kernel, 2, sizeof(cl_uint) * 1, &y);
	clEnqueueNDRangeKernel(m->cl.queue, m->cl.kernel, 1, 0, &workdim, 0, 0, NULL, 0);
}

void	draw_nfract(const t_mlx *m, const t_fract *f,
					unsigned int y, unsigned int n)
{
	t_complex		fact;
	t_complex		c;

	fact.re = (f->max_re - f->min_re) / (IMAGEWIDTH);
	fact.im = (f->max_im - f->min_im) / (IMAGEHEIGHT);
	while (y < n)
	{
		runcl_task(m, y, (cl_double[2]){
				fact.re,
				f->max_im - y * fact.im + f->movey
			});
		y++;
	}
}

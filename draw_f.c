/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 00:45:00 by jye               #+#    #+#             */
/*   Updated: 2018/01/12 06:03:50 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stddef.h>

void	draw_nfract(const t_mlx *m, const t_fract *f,
					unsigned int y, unsigned int n)
{
	t_complex			fact;
	t_complex			c;
	const static size_t	workdim = IMAGEWIDTH;

	fact.re = (f->max_re - f->min_re) / (IMAGEWIDTH);
	fact.im = (f->max_im - f->min_im) / (IMAGEHEIGHT);
	c.re = fact.re;
	c.im = fact.im;
	while (y < n)
	{
		c.im = (f->max_im - y * fact.im) / f->zoom - f->movey;
		clSetKernelArg(m->cl.kernel, 2, sizeof(cl_uint), &y);
		clSetKernelArg(m->cl.kernel, 1, sizeof(cl_double) * 2, &c);
		clEnqueueNDRangeKernel(m->cl.queue, m->cl.kernel, 1, 0, &workdim, 0, 0, NULL, 0);
		y++;
	}
}

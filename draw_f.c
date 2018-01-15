/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 00:45:00 by jye               #+#    #+#             */
/*   Updated: 2018/01/15 03:50:56 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#ifdef __APPLE__
# include <OpenCL/OpenCL.h>
#endif

void	mlx_refresh_image(t_mlx *m, t_fract *f)
{
	mlx_clear_window(m->ptr, m->win);
	clSetKernelArg(m->cl.kernel, 0,
				sizeof(cl_double) * 6 +
				sizeof(cl_uint) * 2,
				f);
	draw_nfract(m, f, 0, IMAGEHEIGHT);
	clEnqueueReadBuffer(m->cl.queue, m->cl.img__, CL_TRUE, 0,
						sizeof(int) * IMAGEWIDTH * IMAGEHEIGHT, m->img__,
						0, 0, 0);
	mlx_put_image_to_window(m->ptr, m->win, m->img, 0, 0);
}

void	draw_nfract(const t_mlx *m, const t_fract *f,
					unsigned int y, unsigned int n)
{
	t_complex			fact;
	const static size_t	workdim = IMAGEWIDTH;

	fact.re = (f->max_re - f->min_re) / (IMAGEWIDTH);
	fact.im = (f->max_im - f->min_im) / (IMAGEHEIGHT);
	clSetKernelArg(m->cl.kernel, 1, sizeof(cl_double) * 2, &fact);
	clEnqueueNDRangeKernel(m->cl.queue, m->cl.kernel, 1, 0,
						&workdim, 0, 0, NULL, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 00:45:00 by jye               #+#    #+#             */
/*   Updated: 2018/01/13 04:19:11 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stddef.h>

void	draw_nfract(const t_mlx *m, const t_fract *f,
					unsigned int y, unsigned int n)
{
	t_complex			fact;
	const static size_t	workdim = IMAGEWIDTH;

	fact.re = (f->max_re - f->min_re) / (IMAGEWIDTH) / f->zoom + f->movex;
	fact.im = (f->max_im - f->min_im) / (IMAGEHEIGHT) / f->zoom + f->movey;
	cl_event event;
	cl_ulong time_start;
	cl_ulong time_end;
	clSetKernelArg(m->cl.kernel, 1, sizeof(cl_double) * 2, &fact);
	clEnqueueNDRangeKernel(m->cl.queue, m->cl.kernel, 1, 0, &workdim, 0, 0, NULL, &event);
	clFinish(m->cl.queue);
	clWaitForEvents(1, &event);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);
	double nanoSeconds = time_end-time_start;
	printf("OpenCl Execution time is: %0.3f milliseconds \n", nanoSeconds / 1000000.0);

}

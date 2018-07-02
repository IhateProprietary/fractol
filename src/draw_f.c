/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 00:45:00 by jye               #+#    #+#             */
/*   Updated: 2018/02/04 06:44:46 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <pthread.h>
#ifdef __APPLE__
# include <OpenCL/OpenCL.h>
#endif

void	mlx_refresh_image(t_mlx *m, t_fract *f)
{
	mlx_clear_window(m->ptr, m->win);
	if (m->frun == GPU_LOAD)
	{
		clSetKernelArg(m->cl.kernel, 0,
					sizeof(cl_double) * 6 +
					sizeof(cl_uint) * 2,
					f);
		draw_gpu(m, f);
		clEnqueueReadBuffer(m->cl.queue, m->cl.img__, CL_TRUE, 0,
					sizeof(int) * IMAGEWIDTH * IMAGEHEIGHT, m->img__,
					0, 0, 0);
	}
	else
		draw_cpu(m, f);
	mlx_put_image_to_window(m->ptr, m->win, m->img, 0, 0);
}

void	draw_gpu(const t_mlx *m, const t_fract *f)
{
	t_complex			fact;
	const static size_t	workdim = IMAGEWIDTH;

	fact.re = (f->max_re - f->min_re) / (IMAGEWIDTH);
	fact.im = (f->max_im - f->min_im) / (IMAGEHEIGHT);
	clSetKernelArg(m->cl.kernel, 1, sizeof(cl_double) * 2, &fact);
	clEnqueueNDRangeKernel(m->cl.queue, m->cl.kernel, 1, 0,
						&workdim, 0, 0, NULL, 0);
}

int		draw_cpu(t_mlx *m, t_fract *f)
{
	int			i;
	pthread_t	mth[N_THREAD];

	i = 0;
	while (i < N_THREAD)
	{
		if (pthread_create(mth + i, NULL, draw_routine,
					(void*[2]){m, f}))
		{
			while (i)
				pthread_kill(mth[i--], SIGKILL);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < N_THREAD)
		pthread_join(mth[i++], NULL);
	return (0);
}

void	*draw_routine(void *param)
{
	static uint64_t	tid_;
	static int		frac = IMAGEHEIGHT / N_THREAD;
	uint64_t		tid;
	t_mlx			*mlx;
	int				y[2];

	mlx = (*((void **)param));
	tid = tid_++ % N_THREAD;
	y[0] = frac * tid;
	y[1] = y[0] + frac;
	draw_nfract(mlx, *((void **)param + 1), y[0], y[1]);
	pthread_exit(NULL);
	return (NULL);
}

void	draw_nfract(const t_mlx *m, const t_fract *f, int y, int max)
{
	t_complex	fact;
	t_complex	z;
	int			x;
	int			cc;

	fact.re = (f->max_re - f->min_re) / (IMAGEWIDTH);
	fact.im = (f->max_im - f->min_im) / (IMAGEHEIGHT);
	z.im = f->max_im - fact.im * y;
	if (f->csetsize)
		cc = f->iteration / f->csetsize;
	while (y < max)
	{
		x = 0;
		z.re = f->min_re;
		while (x < IMAGEWIDTH)
		{
			put_pixel(m->img__, x, y, f->csetsize ?
				f->set[f->nfract(f, z) / cc % f->csetsize].color__ :
				f->nfract(f, z) * 0x00080402);
			z.re += fact.re;
			x++;
		}
		z.im -= fact.im;
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 03:37:58 by jye               #+#    #+#             */
/*   Updated: 2018/07/03 15:39:57 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include <string.h>
#ifdef __APPLE__
# include <OpenCL/OpenCL.h>
#endif

void	cl_reinit_kernel(void *param)
{
	clReleaseKernel(((t_mlx *)*((void **)param))->cl.kernel);
	init_opencl_kernel(((t_mlx *)*((void **)param)),
					((t_fract *)*((void **)param + 1)));
}

int		mlx_keyboard_event(uint64_t event, void *param)
{
	static void				(*event_func[])() = {
		mlx_quit_event,
		mlx_shape_event,
		mlx_zoomopout_event, mlx_zoomopin_event,
		mlx_up_event, mlx_down_event, mlx_right_event,
		mlx_additer_event, mlx_subiter_event, mlx_left_event,
	};
	char					*event_;

	if (event > 0xff)
		return (1);
	else if ((event_ = strchr(MLX_KEY_NFUNC, event)))
		event_func[event_ - MLX_KEY_NFUNC](param);
	else if ((event_ = strchr(MLX_KEY_NFRACTAL, event)))
	{
		mlx_chfractal_event(*((void **)param + 1), event_ - MLX_KEY_NFRACTAL);
		if (((t_mlx *)*((void **)param))->frun == GPU_LOAD)
			cl_reinit_kernel(param);
	}
	mlx_refresh_image(*((void **)param), *((void **)param + 1));
	return (0);
}

void	mlx_quit_event(void *param)
{
	t_mlx	*m;
	t_cl	*cl;
	t_fract *f;

	m = (t_mlx *)*((void **)param);
	f = (t_fract *)*((void **)param + 1);
	if (m->frun == GPU_LOAD)
	{
		cl = &m->cl;
		clReleaseKernel(cl->kernel);
		clReleaseCommandQueue(cl->queue);
		clReleaseProgram(cl->program);
		clReleaseMemObject(cl->img__);
		clReleaseMemObject(cl->cset);
		clReleaseContext(cl->context);
	}
	mlx_destroy_image(m->ptr, m->img);
	mlx_destroy_window(m->ptr, m->win);
	free(f->set);
	exit(0);
}

void	mlx_shape_event(void *param)
{
	((t_fract *)*((void **)param + 1))->flags ^= FRACTAL_CAN_VARY;
}

int		mlx_pointer_event(uint64_t x, uint64_t y, void *param)
{
	t_fract *f;
	t_mlx	*m;

	m = *((void **)param);
	f = *((void **)param + 1);
	if (x > IMAGEWIDTH || y > IMAGEHEIGHT)
		return (1);
	f->x = x;
	f->y = y;
	if (!(f->flags & FRACTAL_CAN_VARY))
		return (0);
	else if (f->flags & FRACTAL_IS_MULTIBROT)
		f->x_re = (double)x / IMAGEWIDTH * 10.0;
	else if (f->flags & FRACTAL_IS_JULIA)
	{
		f->x_re = ((double)x / IMAGEWIDTH) *
			(f->max_re - f->min_re) + f->min_re;
		f->y_im = ((double)y / IMAGEHEIGHT) *
			(f->max_im - f->min_im) + f->min_im;
	}
	mlx_refresh_image(m, f);
	return (0);
}

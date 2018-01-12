/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 01:48:20 by jye               #+#    #+#             */
/*   Updated: 2018/01/12 09:18:43 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <sys/stat.h>

#include <OpenCL/OpenCL.h>

cl_program	cl_get_program(t_cl *cl)
{
	int			fd;
	char		*buf;
	cl_program	program;
	int			ret;
	size_t		zzz = 4096;

	fd = open(".cl", O_RDONLY);
	buf = malloc(4096);
	buf[read(fd, buf, 4095)] = 0;
	program = clCreateProgramWithSource(cl->context, 1,	(const char **)&buf,
										(size_t *)&zzz,
										&ret);
	clBuildProgram(program, 1, &cl->dev_id, 0, 0, 0);
	clGetProgramBuildInfo(program, cl->dev_id, CL_PROGRAM_BUILD_LOG, zzz, buf, &zzz);
	dprintf(1, "error here----:\n%s", buf);
	close(fd);
	free(buf);
	return (program);
}

int		init_opencl(t_mlx *m)
{
	cl_int					ret;
	cl_context_properties	clpro[4] = {CL_CONTEXT_PLATFORM, 0, 0, 0};

	clGetPlatformIDs(1, &m->cl.pla_id, NULL);
	clGetDeviceIDs(m->cl.pla_id, CL_DEVICE_TYPE_GPU, 1, &m->cl.dev_id, NULL);
	clpro[1] = (cl_context_properties)m->cl.pla_id;
	m->cl.context = clCreateContext(clpro, 1, &m->cl.dev_id, NULL, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	m->cl.queue = clCreateCommandQueue(m->cl.context, m->cl.dev_id, 0, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	m->cl.img__ = clCreateBuffer(m->cl.context,
								 CL_MEM_WRITE_ONLY,
								 sizeof(int) * IMAGEWIDTH * IMAGEHEIGHT, 0, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	m->cl.program = cl_get_program(&m->cl);
	return (0);
}

int		init_opencl_kernel(t_mlx *m, t_fract *f)
{
	cl_int		ret;

	if ((m->cl.kernel = clCreateKernel(m->cl.program, f->frac, &ret)) == 0)
		return (ret);
	clSetKernelArg(m->cl.kernel, 0,
				   sizeof(cl_double) * 9 +
				   sizeof(cl_uint) * 2,
				   f);
	clSetKernelArg(m->cl.kernel, 3, sizeof(cl_mem), &m->cl.img__);
	return (ret);
}

void	mlx_refresh_image(t_mlx *m, t_fract *f)
{
	mlx_clear_window(m->ptr, m->win);
	clSetKernelArg(m->cl.kernel, 0,
				   sizeof(cl_double) * 9 +
				   sizeof(cl_uint) * 2,
				   f);
	draw_nfract(m, f, 0, IMAGEHEIGHT);
	clEnqueueReadBuffer(m->cl.queue, m->cl.img__, CL_TRUE, 0,
						sizeof(int) * IMAGEWIDTH * IMAGEHEIGHT, m->img__, 0, 0, 0);
	mlx_put_image_to_window(m->ptr, m->win, m->img, 0, 0);
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
		f->x_re = ((double)x / IMAGEWIDTH) * (f->max_re - f->min_re) + f->min_re;
		f->y_im = ((double)y / IMAGEHEIGHT) * (f->max_im - f->min_im) + f->min_im;
	}
	mlx_refresh_image(m, f);
	return (0);
}

void	mlx_quit_event(void *param);
void	mlx_shape_event(void *param);
void	mlx_zoomin_event(void *param);
void	mlx_zoomout_event(void *param);
void	cl_reinit_kernel(void *param);

int		mlx_keyboard_event(uint64_t event, void *param)
{
	static void				(*event_func[])() = {
		mlx_quit_event,	mlx_shape_event, mlx_zoomout_event, mlx_zoomin_event,
	};
	const static t_fract	nfract[] = {(t_fract){
			.x_re = -1.2, .y_im = 0.160, .flags = FRACTAL_IS_JULIA,
			.min_re = -1.75, .max_re = 1.75, .min_im = -1.0, .max_im = 1.0,
			.movex = 0.0, .movey = 0.0, .frac = "julia", .iteration = 300,
			.zoom = 1.0,
		}, (t_fract){
			.x_re = -1.2, .y_im = 0.160, .flags = 0, .zoom = 1.0,
			.min_re = -1.75, .max_re = 1.75, .min_im = -1.0, .max_im = 1.0, 
			.movex = 0.00, .movey = 0.0, .frac = "mandelbrot", .iteration = 300,
		}, (t_fract){
			.x_re = 5.0, .y_im = 0.160, .flags = FRACTAL_IS_MULTIBROT,
			.min_re = -1.75, .max_re = 1.75, .min_im = -1.0, .max_im = 1.0,
			.movex = 0., .movey = 0.0, .frac = "multibrot", .iteration = 100,
			.zoom = 1.0,
		},
	};
	char		*event_;

	if (event > 0xff)
		return (1);
	else if ((event_ = strchr(MLX_KEY_NFUNC, event)))
		event_func[event_ - MLX_KEY_NFUNC](param);
	else if ((event_ = strchr(MLX_KEY_NFRACTAL, event)))
	{
		*((t_fract *)*((void **)param + 1)) = nfract[event_ - MLX_KEY_NFRACTAL];
		cl_reinit_kernel(param);
	}
	if (event_)
		mlx_refresh_image(*((void **)param), *((void **)param + 1));
	return (0);
}

void	cl_reinit_kernel(void *param)
{
	clReleaseKernel(((t_mlx *)*((void **)param))->cl.kernel);
	init_opencl_kernel(((t_mlx *)*((void **)param)), ((t_fract *)*((void **)param + 1)));
}

void	mlx_quit_event(void *param)
{
	t_mlx	*m;
	t_cl	*cl;

	m = (t_mlx *)*((void **)param);
	cl = &m->cl;
	clReleaseKernel(cl->kernel);
	clReleaseCommandQueue(cl->queue);
	clReleaseProgram(cl->program);
	clReleaseMemObject(cl->img__);
	clReleaseContext(cl->context);
	mlx_destroy_image(m->ptr, m->img);
	mlx_destroy_window(m->ptr, m->win);
	exit(0);
}

void	mlx_shape_event(void *param)
{
	((t_fract *)*((void **)param + 1))->flags ^= FRACTAL_CAN_VARY;
}

# define ZOOM_VALUE 1.1

void	mlx_zoomin_event(void *param)
{
	/* t_fract *f; */
	/* double	x; */
	/* double	y; */

	/* f = ((t_fract *)*((void **)param + 1)); */
	/* f->zoom *= ZOOM_VALUE; */
	/* f->movex = f->movex + (f->); */
	/* f->itzoom += 1; */
}

void	mlx_zoomout_event(void *param)
{
	/* t_fract *f; */
	/* double	x; */
	/* double	y; */

	/* f = ((t_fract *)*((void **)param + 1)); */
	/* if (f->itzoom == 0) */
	/* 	return ; */
	/* f->zoom /= ZOOM_VALUE; */
	/* f->movex -= (f->x - IMAGEWIDTH / 2) / IMAGEWIDTH / f->zoom; */
	/* f->movey -= (f->y - IMAGEHEIGHT / 2) / IMAGEHEIGHT / f->zoom; */
	/* f->itzoom -= 1; */
}

int		main(int ac, char **av)
{
	t_mlx	mlx;
	t_fract	f;

	if (init_mlx_win(&mlx) || init_mlx_img(&mlx))
		return (1);
	f = (t_fract){
		.x_re = -1.2, .y_im = 0.160,
		.min_re = -2.25, .max_re = 1.25, .min_im = -1.0, .max_im = 1.0,
		.movex = -0.00, .movey = 0.0, .zoom = 1.0,
		.frac = "mandelbrot", .iteration = 300,
		.flags = 0, .itzoom = 0
	};
	init_opencl(&mlx);
	init_opencl_kernel(&mlx, &f);
	draw_nfract(&mlx, &f, 0, IMAGEHEIGHT);
	clEnqueueReadBuffer(mlx.cl.queue, mlx.cl.img__, CL_TRUE, 0,
						sizeof(int) * IMAGEWIDTH * IMAGEHEIGHT, mlx.img__, 0, 0, 0);
	mlx_hook(mlx.win, 6, 0, mlx_pointer_event, (void*[2]){&mlx, &f});
	mlx_key_hook(mlx.win, mlx_keyboard_event, (void*[2]){&mlx, &f});
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.ptr);
}

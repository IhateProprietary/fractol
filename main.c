/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 01:48:20 by jye               #+#    #+#             */
/*   Updated: 2018/01/09 02:34:06 by jye              ###   ########.fr       */
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
	buf[read(fd, buf, 4096)] = 0;
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
		return (1);
	clSetKernelArg(m->cl.kernel, 0,
				   sizeof(cl_double) * 9 +
				   sizeof(cl_uint) * 2,
				   f);
	clSetKernelArg(m->cl.kernel, 3, sizeof(cl_mem), &m->cl.img__);
	return (0);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;
//	char	*cset;
	t_fract	f;

	if (init_mlx_win(&mlx) || init_mlx_img(&mlx))
		return (1);
	f = (t_fract){
		.x_re = -1.2,
		.y_im = 0.160,
		.min_re = -2.5, .max_re = 1.0, .min_im = -1.0,
		.max_im = 1.0,
		.movex = 0.75, .movey = -0,
		.frac = "julia",
		.iteration = 200
	};
	init_opencl(&mlx);
//	init_color_set(&mlx, &f, cset);
	init_opencl_kernel(&mlx, &f);
	draw_nfract(&mlx, &f, 0, IMAGEHEIGHT);
	clEnqueueReadBuffer(mlx.cl.queue, mlx.cl.img__, CL_TRUE, 0,
						sizeof(int) * IMAGEWIDTH * IMAGEHEIGHT, mlx.img__, 0, 0, 0);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.ptr);
}

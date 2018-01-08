/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 01:48:20 by jye               #+#    #+#             */
/*   Updated: 2018/01/08 01:12:07 by jye              ###   ########.fr       */
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
	read(fd, buf, 4096);
	program = clCreateProgramWithSource(cl->context, 1,	(const char **)&buf,
										(size_t *)&zzz,
										&ret);
	clBuildProgram(program, 1, &cl->dev_id, 0, 0, 0);
	clGetProgramBuildInfo(program, cl->dev_id, CL_PROGRAM_BUILD_LOG, zzz, buf, &zzz);
	dprintf(1, "%s\n", buf);
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
	m->cl.queue = clCreateCommandQueue(m->cl.context, m->cl.dev_id, 0, &ret);
	if (ret != CL_SUCCESS)
		return (1);
	m->cl.img__ = clCreateBuffer(m->cl.context,
								 CL_MEM_WRITE_ONLY,
								 m->img_size * IMAGEHEIGHT, 0, &ret);
	if (ret != CL_SUCCESS)
		return (1);
	m->cl.program = cl_get_program(&m->cl);
	return (0);
}

int		init_opencl_kernel(t_mlx *m, t_fract *f)
{
	cl_int		ret;

	if ((m->cl.kernel = clCreateKernel(m->cl.program, f->frac, &ret)) == 0)
		return (1);
	clSetKernelArg(m->cl.kernel, 0,
				   sizeof(cl_double) * 2 +
				   sizeof(cl_uint) * 2 +
				   sizeof(cl_double) * 7,
				   f);
	clSetKernelArg(m->cl.kernel, 3, sizeof(cl_int), &m->img_size);
	clSetKernelArg(m->cl.kernel, 5, sizeof(cl_mem), &m->cl.img__);
	clSetKernelArg(m->cl.kernel, 4, sizeof(cl_mem), &m->cl.cset);
	return (0);
}

int		init_color_set(t_mlx *m, t_fract *f, char *cset)
{
	static t_mlxcolor	set[] = {
		{.color__ = 0},
		{.color.b = 0xff}
	};
	int					ret;

	if (cset == NULL)
	{
		m->cl.cset = clCreateBuffer(m->cl.context, CL_MEM_READ_ONLY,
									sizeof(int) * 2, 0, &ret);
		ret = clEnqueueReadBuffer(m->cl.queue, m->cl.cset, CL_TRUE, 0,
								   sizeof(int) * 2, &set, 0, 0, 0);

		f->csetsize = 2;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;
	char	*cset;
	t_fract	f;

	if (init_mlx_win(&mlx) || init_mlx_img(&mlx))
		return (1);
	cset = 0;
	f = (t_fract){
		.x_re = -1.2,
		.y_im = 0.160,
		.min_re = -2.5, .max_re = 1, .min_im = -1.0,
		.max_im = 1.0,
		.movex = 0.0, .movey = 0.0,
		.frac = "julia",
		.iteration = 1000
	};
	init_opencl(&mlx);
	init_color_set(&mlx, &f, cset);
	init_opencl_kernel(&mlx, &f);
//	init_draw_routine(&mlx, &f);
	draw_nfract(&mlx, &f, (unsigned int[2]){0, 1});
//	dprintf(1, "%d\n", *(int *)mlx.img__);
	clEnqueueReadBuffer(mlx.cl.queue, mlx.cl.img__, CL_TRUE, 0,
						mlx.img_size * IMAGEHEIGHT, mlx.img__, 0, 0, 0);
	dprintf(1, "-------------------------\n");
	for (int i = 0; i < IMAGEWIDTH; i++)
	{
		dprintf(2, "%d\n", ((uint *)mlx.img__)[i]);
	}
//	dprintf(1, "%d\n", *(int *)mlx.img__);
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.ptr);
}

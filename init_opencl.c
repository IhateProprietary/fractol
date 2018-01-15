/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 03:31:01 by jye               #+#    #+#             */
/*   Updated: 2018/01/15 04:40:43 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#ifdef __APPLE__
# include <OpenCL/OpenCL.h>
#endif

#define BUFFER_SIZE 4096

cl_program	cl_get_program(t_cl *cl)
{
	int			fd;
	char		*buf;
	cl_program	program;
	int			ret;
	size_t		zzz;

	fd = open(".cl", O_RDONLY);
	zzz = BUFFER_SIZE;
	if ((buf = (char *)malloc(BUFFER_SIZE)) == 0)
		return (0);
	if ((ret = read(fd, buf, BUFFER_SIZE - 1)) <= 0)
		return (0);
	buf[ret] = 0;
	program = clCreateProgramWithSource(cl->context, 1, (const char **)&buf,
										(size_t *)&zzz, &ret);
	clBuildProgram(program, 1, &cl->dev_id,
				"-D IMAGEHEIGHT=1080 -D IMAGEWIDTH=1920", 0, 0);
	clGetProgramBuildInfo(program, cl->dev_id,
					CL_PROGRAM_BUILD_LOG, zzz, buf, &zzz);
	if (*buf != 0)
		dprintf(2, "oops CL compiler told me your code suckz.\n"
				"Here have some error\n%s", buf);
	close(fd);
	free(buf);
	return (program);
}

int			init_opencl(t_mlx *m)
{
	cl_int					ret;
	cl_context_properties	fucknorm[3];

	clGetPlatformIDs(1, &m->cl.pla_id, NULL);
	clGetDeviceIDs(m->cl.pla_id, CL_DEVICE_TYPE_GPU, 1, &m->cl.dev_id, NULL);
	fucknorm[0] = CL_CONTEXT_PLATFORM;
	fucknorm[1] = (cl_context_properties)m->cl.pla_id;
	fucknorm[2] = 0;
	m->cl.context = clCreateContext(fucknorm, 1, &m->cl.dev_id,
									NULL, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	m->cl.queue = clCreateCommandQueue(m->cl.context, m->cl.dev_id,
								0, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	m->cl.img__ = clCreateBuffer(m->cl.context, CL_MEM_WRITE_ONLY,
							sizeof(int) * IMAGEWIDTH * IMAGEHEIGHT, 0, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	if ((m->cl.program = cl_get_program(&m->cl)))
		return (1);
	return (0);
}

int			init_opencl_kernel(t_mlx *m, t_fract *f)
{
	cl_int		ret;

	if ((m->cl.kernel = clCreateKernel(m->cl.program, f->frac, &ret)) == 0)
		return (ret);
	clSetKernelArg(m->cl.kernel, 0,
				sizeof(cl_double) * 6 +
				sizeof(cl_uint) * 2,
				f);
	clSetKernelArg(m->cl.kernel, 2, sizeof(cl_mem), &m->cl.img__);
	return (ret);
}

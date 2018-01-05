/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 01:48:20 by jye               #+#    #+#             */
/*   Updated: 2018/01/05 06:25:20 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __APPLE__
# include <OpenCL/OpenCl.h>
#else
# error "SORRY AIN'T NO FUCKING PORTABLE CODE\n"
#endif

/* int		main(int ac, char **av) */
/* { */
/* 	t_mlx	mlx; */
/* 	t_fract	f; */

/* 	if (init_mlx_win(&mlx) || init_mlx_img(&mlx)) */
/* 		return (1); */
/* 	f = (t_fract){ */
/* 		.x_re = -1.2, */
/* 		.y_im = 0.160, */
/* 		.min_re = -2.5, .max_re = 1, .min_im = -1.0, */
/* 		.max_im = 1.0, */
/* 		.movex = 0.00, .movey = 0.0, */
/* 		.fract_ = mandelbrot_, */
/* 		.iteration = 1000 */
/* 	}; */
/* 	init_draw_routine(&mlx, &f); */
/* 	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0); */
/* 	mlx_loop(mlx.ptr); */
/* } */

int		main(int ac, char **av)
{
	char	zzz[2048];
	size_t	zzzz;
	cl_platform_id	pla_id;
	cl_device_id	dev_id;
	cl_context_properties clpro[3] = {CL_CONTEXT_PLATFORM, 0, 0};
	cl_context	clcon;
	cl_int	err_ret;

	clGetPlatformIDs(1, &pla_id, NULL);
	clGetDeviceIDs(pla_id, CL_DEVICE_TYPE_GPU, 1, &dev_id, NULL);
	clpro[1] = (cl_context_properties)pla_id;
	clcon = clCreateContext(clpro, 1, &dev_id, NULL, NULL, &err_ret);
	return (0);
}

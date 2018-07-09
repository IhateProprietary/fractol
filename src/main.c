/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 01:48:20 by jye               #+#    #+#             */
/*   Updated: 2018/07/03 17:02:19 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include "ft_printf.h"
#include <stddef.h>
#include <stdlib.h>
#ifdef __APPLE__
# include <OpenCL/OpenCL.h>
#endif

int		init_gpu_run(t_mlx *mlx, t_fract *f)
{
	t_cl	*cl;

	if (init_opencl(mlx, f))
		exit(1);
	if (init_opencl_kernel(mlx, f))
	{
		ft_dprintf(2, "fractol: somewhere in opencl caught fire.\n");
		cl = &mlx->cl;
		if (cl->context)
			clReleaseContext(cl->context);
		if (cl->program)
			clReleaseProgram(cl->program);
		if (cl->queue)
			clReleaseCommandQueue(cl->queue);
		if (cl->img__)
			clReleaseMemObject(cl->img__);
		if (cl->cset)
			clReleaseMemObject(cl->cset);
		if (cl->kernel)
			clReleaseKernel(cl->kernel);
		ft_dprintf(2, "fractol: switching to CPU.");
		return (1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;
	t_fract	f;

	ft_memset(&mlx.cl, 0, sizeof(t_cl));
	if (init_mlx_win(&mlx) || init_mlx_img(&mlx))
	{
		ft_dprintf(2, "fractol: good grief, why did I use mlx.\n");
		return (1);
	}
	if (option_parse(ac, av, &mlx, &f))
		return (1);
	if (parse_color(&f))
	{
		ft_dprintf(2, "fractol: your color broke EVERYTHING,"
				" uncool maaaaaan, uncoooooool.\n");
		return (1);
	}
	if (init_gpu_run(&mlx, &f))
		mlx.frun = CPU_LOAD;
	mlx_hook(mlx.win, 6, 0, mlx_pointer_event, (void*[2]){&mlx, &f});
	mlx_key_hook(mlx.win, mlx_keyboard_event, (void*[2]){&mlx, &f});
	mlx_mouse_hook(mlx.win, mlx_mousek_hook, (void*[2]){&mlx, &f});
	mlx_refresh_image(&mlx, &f);
	mlx_loop(mlx.ptr);
}

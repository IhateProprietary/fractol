/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 01:48:20 by jye               #+#    #+#             */
/*   Updated: 2018/01/18 04:54:12 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"
#include "ft_printf.h"
#include "ft_getopt_long.h"
#include <stddef.h>

int		parse_fractal(t_fract *f, char *arg)
{
	const static uint64_t			hash_f[] = {
		0x53de0000013d660bULL, 0x1e274b61b827ab68ULL,
		0xf8240391b2e8e92aULL
	};
	uint64_t						khash;
	int								i;

	khash = 0;
	while (*arg)
	{
		khash *= 281474976710677;
		khash ^= *arg | ((*arg << 16) << 16);
		arg++;
	}
	i = 0;
	while (i < MAX_FRACTALS)
	{
		if (hash_f[i] == khash)
		{
			mlx_chfractal_event(f, i);
			break ;
		}
		++i;
	}
	return (i >= MAX_FRACTALS);
}

int		option_parse(int ac, char **av, t_fract *f)
{
	static struct s_options long_opt[] = {
		{.s = "fractal", .has_arg = req_arg, NULL, 'f'},
		{.s = "color", .has_arg = req_arg, NULL, 'c'},
		{0, 0, 0, 0}
	};
	int						ret;
	char					*s;

	f->frac = 0;
	s = 0;
	while ((ret = ft_getopt_long(ac, av, NULL, long_opt)) != -1)
	{
		if (ret == 'f' && parse_fractal(f, g_optarg_) &&
			ft_dprintf(2, "fractol: "
					"ur fractal is wrong and you should feel bad.\n"))
			return (1);
		else if (ret == 'c')
			s = g_optarg_;
		else if (ret == '?')
			return (1);
	}
	if (f->frac == 0)
		mlx_chfractal_event(f, 1);
	f->color = s;
	return (0);
}

int		main(int ac, char **av)
{
	t_mlx	mlx;
	t_fract	f;

	if (init_mlx_win(&mlx) || init_mlx_img(&mlx))
	{
		ft_dprintf(2, "fractol: good grief, why did I use mlx.\n");
		return (1);
	}
	if (option_parse(ac, av, &f))
		return (1);
	if (parse_color(&f))
	{
		ft_dprintf(2, "fractol: your color broke EVERYTHING,"
				" uncool maaaaaan, uncoooooool.\n");
		return (1);
	}
	if (init_opencl(&mlx, &f) || init_opencl_kernel(&mlx, &f))
	{
		ft_dprintf(2, "fractol: somewhere in opencl caught fire.\n");
		return (1);
	}
	mlx_hook(mlx.win, 6, 0, mlx_pointer_event, (void*[2]){&mlx, &f});
	mlx_key_hook(mlx.win, mlx_keyboard_event, (void*[2]){&mlx, &f});
	mlx_refresh_image(&mlx, &f);
	mlx_loop(mlx.ptr);
}

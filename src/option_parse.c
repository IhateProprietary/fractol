/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 01:47:31 by jye               #+#    #+#             */
/*   Updated: 2018/02/08 03:43:46 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getopt_long.h"
#include "fractol.h"
#include "ft_printf.h"
#include <stddef.h>
#ifdef __APPLE__
# include <OpenCL/OpenCL.h>
#endif

static int		parse_fractal(t_fract *f, char *arg)
{
	const static uint64_t			hash_f[] = {
		0x53de0000013d660bULL, 0x1e274b61b827ab68ULL,
		0xf8240391b2e8e92aULL
	};
	uint64_t						khash;
	int								i;

	khash = hash_string(arg);
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

static int		parse_run_option(t_mlx *m, uint64_t khash)
{
	if (khash == 0x107600000000a84aUL)
		m->frun = GPU_LOAD;
	else if (khash == 0x108e00000000b16eUL)
		m->frun = CPU_LOAD;
	else
		return (1);
	return (0);
}

static int		set_option(t_mlx *m, t_fract *f, int ret)
{
	uint64_t	khash;
	char		*s;

	s = f->color;
	if (ret == 'f' && parse_fractal(f, optarg_) &&
		ft_dprintf(2, "fractol: "
			"ur fractal is wrong and you should feel bad.\n"))
		return (1);
	else if (ret == 'c')
		s = optarg_;
	else if (ret == 'r')
	{
		khash = hash_string(optarg_);
		if (parse_run_option(m, khash))
		{
			ft_dprintf(2, "fractol: Duuuuuude I can't"
				" run with '%s'...\n", optarg_);
			return (1);
		}
	}
	else if (ret == '?')
		return (1);
	f->color = s;
	return (0);
}

int				option_parse(int ac, char **av, t_mlx *mlx, t_fract *f)
{
	static struct s_options long_opt[] = {
		{.s = "fractal", .has_arg = req_arg, NULL, 'f'},
		{.s = "color", .has_arg = req_arg, NULL, 'c'},
		{.s = "run", .has_arg = req_arg, NULL, 'r'},
		{0, 0, 0, 0}
	};
	int						ret;

	f->frac = 0;
	f->color = 0;
	mlx->frun = GPU_LOAD;
	while ((ret = ft_getopt_long(ac, av, NULL, long_opt)) != -1)
		if (set_option(mlx, f, ret))
			return (1);
	if (f->frac == 0)
		mlx_chfractal_event(f, 1);
	return (0);
}

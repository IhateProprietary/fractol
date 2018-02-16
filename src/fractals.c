/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 04:45:57 by jye               #+#    #+#             */
/*   Updated: 2018/01/26 05:04:24 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mlx_chfractal_event(t_fract *f, int n)
{
	int						csetsize;
	static t_fract			nfract[3] = {{N_XD, O_XD, R_XD, M_XD
		, FRACTAL_IS_MULTIBROT}};

	csetsize = f->csetsize;
	if (n >= MAX_FRACTALS)
		return (1);
	*f = nfract[n];
	f->csetsize = csetsize;
	return (0);
}

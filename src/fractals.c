/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 04:45:57 by jye               #+#    #+#             */
/*   Updated: 2018/07/03 15:13:42 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mlx_chfractal_event(t_fract *f, int n)
{
	t_fract					fract_cp;
	static t_fract			nfract[3] = {{N_XD, R_XD, I_XD, NE_XD
		, FRACTAL_IS_MULTIBROT}};

	fract_cp = *f;
	if (n >= MAX_FRACTALS)
		return (1);
	*f = nfract[n];
	f->csetsize = fract_cp.csetsize;
	f->color = fract_cp.color;
	f->set = fract_cp.set;
	return (0);
}

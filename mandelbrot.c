/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 01:10:27 by jye               #+#    #+#             */
/*   Updated: 2018/01/06 04:12:40 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mandelbrot_(const t_fract *f, double r, double i)
{
	unsigned int	n;
	double			r2;
	double			i2;
	double			ti;
	double			tr;

	n = 0;
	ti = i;
	tr = r;
	while (n < f->iteration)
	{
		i2 = i * i;
		r2 = r * r;
		if ((i2 + r2) > 4.0)
			break;
		i = 2 * r * i + ti;
		r = r2 - i2 + tr;
		n++;
	}
	return (n);
}

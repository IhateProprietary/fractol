/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 08:47:49 by jye               #+#    #+#             */
/*   Updated: 2018/02/03 09:59:37 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

int mandelbrot(t_fract *f, t_complex c)
{
	t_complex	z;
	t_complex	c2;
	uint		n;

	n = 0;
	z.im = c.im;
	z.re = c.re;
	while (n < f->iteration)
	{
		c2.im = z.im * z.im;
		c2.re = z.re * z.re;
		if ((c2.im + c2.re) > 4.0)
			break;
		z.im = 2.0 * z.re * z.im + c.im;
		z.re = c2.re - c2.im + c.re;
		n++;
	}
	return (n);
}

int julia(t_fract *f, t_complex c)
{
	t_complex	z;
	t_complex	c2;
	uint		n;

	n = 0;
	z.im = c.im;
	z.re = c.re;
	while (n < f->iteration)
	{
		c2.im = z.im * z.im;
		c2.re = z.re * z.re;
		if ((c2.im + c2.re) > 4.0)
			break;
		z.im = 2.0 * z.re * z.im + f->y_im;
		z.re = c2.re - c2.im + f->x_re;
		n++;
	}
	return (n);
}

int multibrot(t_fract *f, t_complex c)
{
	t_complex	z;
	t_complex	c2;
	double		tmp;
	uint		n;

	n = 0;
	z.im = c.im;
	z.re = c.re;
	while (n < f->iteration)
	{
		tmp = atan2(z.im, z.re) * f->x_re;
		c2.im = z.im * z.im;
		c2.re = z.re * z.re;
		if ((c2.im + c2.re) > 4.0)
			break;
		z.im = pow((c2.re + c2.im), (f->x_re/2.0)) * sin(tmp) + c.im;
		z.re = pow((c2.re + c2.im), (f->x_re/2.0)) * cos(tmp) + c.re;
		n++;
	}
	return (n);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 05:43:32 by jye               #+#    #+#             */
/*   Updated: 2018/01/05 02:01:42 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia_(const t_fract *f, double r, double i)
{
	unsigned int	n;
	double			r2;
	double			i2;

	n = 0;
	while (n < f->iteration)
	{
		i2 = i * i;
		r2 = r * r;
		if ((i2 + r2) > 4.0)
			break;
		i = 2 * r * i + f->y_im;
		r = r2 - i2 + f->x_re;
		++n;
	}
	return (n);
}

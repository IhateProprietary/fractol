/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 00:45:00 by jye               #+#    #+#             */
/*   Updated: 2018/01/05 02:02:35 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_fractal_pixel(const t_mlx *m, const t_fract *f,
						  const t_complex *c, const unsigned int x[2])
{
	int		n;

	n = f->fract_(f, c->re, c->im);
	put_pixel(m->img__, x[0], x[1],
		((t_mlxcolor){
			.color.r = (n * 2) % 256,
			.color.g = (n) % 256,
			.color.b = (n) % 256
		}).color__);
}

void	draw_nfract(const t_mlx *m, const t_fract *f, unsigned int y, unsigned int n)
{
	t_complex		fact;
	t_complex		c;
	unsigned int	x;

	x = 0;
	fact.re = (f->max_re - f->min_re) / (IMAGEWIDTH);
	fact.im = (f->max_im - f->min_im) / (IMAGEHEIGHT);
	while (y < n)
	{
		c.im = f->max_im - y * fact.im + f->movey;
		while (x < IMAGEWIDTH)
		{
			c.re = f->min_re + x * fact.re + f->movex;
			set_fractal_pixel(m, f, &c, (const unsigned int[2]){x, y});
			++x;
		}
		x = 0;
		++y;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 01:39:41 by jye               #+#    #+#             */
/*   Updated: 2018/01/03 01:35:16 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define XSIZE(x, type) ((x) * sizeof(type))
#define DPTR__(x, y, xs, type) (XSIZE(x, type) + XSIZE(y * xs, type)))
#define PTR__(ptr, x, y, xs, type) (*((type *)((ptr) + DPTR__(x, y, xs, type)))

void	put_pixel(void *img_ptr, int x, int y, int color)
{
	PTR__(img_ptr, x, y, IMAGEWIDTH, int) = color;
}

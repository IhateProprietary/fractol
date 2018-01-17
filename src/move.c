/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 03:29:40 by jye               #+#    #+#             */
/*   Updated: 2018/01/15 03:30:23 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define MOVE_RATIO 0.01

void	mlx_left_event(void *param)
{
	t_fract *f;
	double	move;

	f = ((t_fract *)*((void **)param + 1));
	move = (f->max_re - f->min_re) * MOVE_RATIO;
	f->max_re -= move;
	f->min_re -= move;
}

void	mlx_right_event(void *param)
{
	t_fract *f;
	double	move;

	f = ((t_fract *)*((void **)param + 1));
	move = (f->max_re - f->min_re) * MOVE_RATIO;
	f->max_re += move;
	f->min_re += move;
}

void	mlx_up_event(void *param)
{
	t_fract *f;
	double	move;

	f = ((t_fract *)*((void **)param + 1));
	move = (f->max_im - f->min_im) * MOVE_RATIO;
	f->max_im += move;
	f->min_im += move;
}

void	mlx_down_event(void *param)
{
	t_fract *f;
	double	move;

	f = ((t_fract *)*((void **)param + 1));
	move = (f->max_im - f->min_im) * MOVE_RATIO;
	f->max_im -= move;
	f->min_im -= move;
}

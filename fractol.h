/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 01:41:19 by jye               #+#    #+#             */
/*   Updated: 2018/01/05 04:47:10 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#  include "fucknorm1.h"
# else
#  include "fucknorm2.h"
# endif

# define IMAGEHEIGHT 	1080
# define IMAGEWIDTH		1900
# define PROGRAM_NAME	"fractol"

typedef union	u_mlxcolor
{
	t_color color;
	int		color__;
}				t_mlxcolor;

typedef struct	s_complex
{
	double re;
	double im;
}				t_complex;

typedef struct	s_fract
{
	double			x_re;
	double			y_im;
	double			min_re;
	double			max_re;
	double			min_im;
	double			max_im;
	double			zoom;
	double			movex;
	double			movey;
	int				(*fract_)(const struct s_fract *, double, double);
	int				iteration;
}				t_fract;

typedef struct	s_mlx
{
	void	*ptr;
	void	*win;
	void	*img;
	void	*img__;
	size_t	imageh;
	size_t	imagew;
}				t_mlx;

/*
** mlx bullshit
*/

int				init_mlx_win(t_mlx *mlx);
int				init_mlx_img(t_mlx *mlx);
void			put_pixel(void *img_ptr, int x, int y, int color);

/*
** fractals / nfunction
*/

void			draw_nfract(const t_mlx *m, const t_fract *f,
							unsigned int y, unsigned int n);
int				julia_(const t_fract *f, double r, double i);
int				mandelbrot_(const t_fract *f, double r, double i);

/*
** multithread draw fractal routine
*/

int				init_draw_routine(t_mlx *mlx, t_fract *f);

#endif

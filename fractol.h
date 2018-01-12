/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 01:41:19 by jye               #+#    #+#             */
/*   Updated: 2018/01/12 05:47:44 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# ifdef __APPLE__
#  include <OpenCL/OpenCL.h>
# endif

# include <stdlib.h>
# include <stddef.h>
# if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#  include "fucknorm1.h"
# else
#  include "fucknorm2.h"
# endif

# define IMAGEHEIGHT 	1080
# define IMAGEWIDTH		1920
# define PROGRAM_NAME	"fractol"
# define FRACTAL_IS_MULTIBROT 0x2
# define FRACTAL_IS_JULIA	  0x1
# define FRACTAL_CAN_VARY	  0x4

# define MLX_KEY_ESC	0x35
# define MLX_KEY_ONE	0x12
# define MLX_KEY_TWO	0x13
# define MLX_KEY_THREE	0x14
# define MLX_KEY_FOUR	0x15
# define MLX_KEY_STAR	0x43
# define MLX_KEY_MINUS	0x4e
# define MLX_KEY_PLUS	0x45

# define MLX_KEY_NFUNC		"\x35\x43\x4e\x45"
# define MLX_KEY_NFRACTAL	"\x12\x13\x14"

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
	cl_double	x_re;
	cl_double	y_im;
	cl_uint		iteration;
	cl_uint		csetsize;
	double		min_re;
	double		max_re;
	double		min_im;
	double		max_im;
	double		movex;
	double		movey;
	double		zoom;
	char		*frac;
	double		x;
	double		y;
	uint32_t	flags;
	int			itzoom;
}				t_fract;

typedef struct	s_cl
{
	cl_device_id		dev_id;
	cl_platform_id		pla_id;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				img__;
	cl_mem				cset;
}				t_cl;

typedef struct	s_mlx
{
	void	*ptr;
	void	*win;
	void	*img;
	void	*img__;
	cl_int	img_size;
	t_cl	cl;
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

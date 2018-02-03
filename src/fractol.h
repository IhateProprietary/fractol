/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 01:41:19 by jye               #+#    #+#             */
/*   Updated: 2018/01/26 05:04:00 by jye              ###   ########.fr       */
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

# define MAX_FRACTALS	3
# define MAX_COLORS		20

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
# define MLX_KEY_W		0xd
# define MLX_KEY_A		0x0
# define MLX_KEY_S		0x1
# define MLX_KEY_D		0x2
# define MLX_KEY_PUP	0x74
# define MLX_KEY_PDOWN	0x79

# define MLX_KEY_NFUNC		"\x35\x43\x4e\x45\xd\x1\x2\x74\x79"
# define MLX_KEY_NFRACTAL	"\x12\x13\x14"

typedef union	u_mlxcolor
{
	t_color		color;
	uint32_t	color__;
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
	char		*frac;
	char		*color;
	t_mlxcolor	*set;
	uint32_t	x;
	uint32_t	y;
	uint32_t	flags;
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
void			mlx_refresh_image(t_mlx *m, t_fract *f);

/*
** fractals / nfunction
*/

void			draw_nfract(const t_mlx *m, const t_fract *f);
int				parse_color(t_fract *f);

/*
** key event
*/
int				mlx_pointer_event(uint64_t x, uint64_t y, void *param);
void			mlx_quit_event(void *param);
void			mlx_shape_event(void *param);
void			mlx_zoomopin_event(void *param);
void			mlx_zoomopout_event(void *param);
void			mlx_zoomin_event(void *param);
void			mlx_zoomout_event(void *param);
int				mlx_chfractal_event(t_fract *f, int n);
void			mlx_right_event(void *param);
void			mlx_left_event(void *param);
void			mlx_up_event(void *param);
void			mlx_down_event(void *param);
void			cl_reinit_kernel(void *param);
void			mlx_additer_event(void *param);
void			mlx_subiter_event(void *param);
int				mlx_keyboard_event(uint64_t event, void *param);

/*
** opencl
*/

int				init_opencl_kernel(t_mlx *m, t_fract *f);
int				init_opencl(t_mlx *m, t_fract *f);
cl_program		cl_get_program(t_cl *cl);

# define N_XD -1.2, 0.160, 300, 0, -1.75, 1.75, -1.0, 1.0, "julia", 0
# define O_XD 0, 0, 0, FRACTAL_IS_JULIA}, {-1.2, 0.160, 300, 0, -2.25, 1.25
# define R_XD -1.0, 1.0, "mandelbrot", 0, 0, 0, 0, 0}, {3.0, 0.160, 300, 0
# define M_XD -1.75, 1.75, -1.0, 1.0, "multibrot", 0, 0, 0, 0

#endif

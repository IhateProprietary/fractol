typedef struct
{
	double	x_re;
	double	y_im;
	uint	iteration;
	uint	csetsize;
	double	min_re;
	double	max_re;
	double	min_im;
	double	max_im;
	double	movex;
	double	movey;
	double	zoom;
}	fract_t;

typedef struct
{
	double re;
	double im;
}	complex_t;

typedef struct
{
	uint y;
	uint x;
}	graph_t;

__kernel void julia(fract_t f,
					complex_t fact,
					graph_t g,
					__global __write_only uint *img_ptr)
{
	complex_t	c;
	double		r2;
	double		i2;
	uint		n;

	g.x = get_global_id(0);
	c.re = (f.min_re + g.x * fact.re) / f.zoom + f.movex;
	c.im = fact.im;
	for (n = 0; n < f.iteration; n++)
	{
		i2 = c.im * c.im;
		r2 = c.re * c.re;
		if ((i2 + r2) > 4.0)
			break;
		c.im = 2.0 * c.re * c.im + f.y_im;
		c.re = r2 - i2 + f.x_re;
	}
	*(img_ptr + (g.x + g.y * 1920)) = n * 0x00111111;
}

__kernel void mandelbrot(fract_t f,
						 complex_t fact,
						 graph_t g,
						 __global __write_only uint *img_ptr)
{
	complex_t	c;
	double		r2;
	double		i2;
	uint		n;

	g.x = get_global_id(0);
	fact.re = (f.min_re + g.x * fact.re) / f.zoom + f.movex;
	c.re = fact.re;
	c.im = fact.im;
	for (n = 0; n < f.iteration; n++)
	{
		i2 = c.im * c.im;
		r2 = c.re * c.re;
		if ((i2 + r2) > 4.0)
			break;
		c.im = 2.0 * c.re * c.im + fact.im;
		c.re = r2 - i2 + fact.re;
	}
	*(img_ptr + (g.x + g.y * 1920)) = n * 0x00111111;
}

#pragma OPENCL EXTENSION cl_khr_fp64 : enable

__kernel void multibrot(fract_t f,
						complex_t fact,
						graph_t g,
						__global __write_only uint *img_ptr)
{
	complex_t	c;
	double		tmp;
	double		tmpi;
	uint		n;

	g.x = get_global_id(0);
	fact.re = (f.min_re + g.x * fact.re) / f.zoom + f.movex;
	c.re = fact.re;
	c.im = fact.im;
	for (n = 0; n < f.iteration; n++)
	{
		tmp = atan2(c.im, c.re) * f.x_re;
		c.im = c.im * c.im;
		c.re = c.re * c.re;
		if ((c.im + c.re) > 4.0)
			break;
		tmpi = c.im;
		c.im = pow((c.re + c.im), (f.x_re/2.0)) * sin(tmp) + fact.im;
		c.re = pow((c.re + tmpi), (f.x_re/2.0)) * cos(tmp) + fact.re;
	}
	*(img_ptr + (g.x + g.y * 1920)) = n * 0x00111111;
}

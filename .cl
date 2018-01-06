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
	double	zoom;
	double	movex;
	double	movey;
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
					int size_line,
					__constant __read_only uint *cset,
					__global __write_only uint *img_ptr)
{
	uint		n;
	complex_t	c;
	double		r2;
	double		i2;

	n = 0;
	g.x = get_global_id(0);
	c.re = f.max_im - g.y * fact.im + f.movey;
	c.im = f.min_re + g.x * fact.re + f.movex;
	while (n < f.iteration)
	{
		i2 = c.im * c.im;
		r2 = c.re * c.re;
		if ((i2 + r2) > 4.0)
			break;
		c.im = 2 * c.re * c.im + f.y_im;
		c.re = r2 - i2 + f.x_re;
		++n;
	}
	*(img_ptr + (g.x + g.y * 1920)) = n;
}

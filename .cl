#pragma OPENCL EXTENSION cl_khr_fp64 : enable

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
}	fract_t;

__kernel void julia(fract_t f,
					double2 fact,
					__constant __read_only uint *cset,
					__global __write_only uint *img_ptr)
{
	double2		c;
	double2		c2;
	uint2		g;
	uint		n;

	g.x = get_global_id(0);
	c.x = (f.min_re + g.x * fact.x);
	c.y = f.max_im;
	for (g.y = 0; g.y < IMAGEHEIGHT; g.y++)
	{
		double2	z = {c.x, c.y};
		for (n = 0; n < f.iteration; n++)
		{
			c2.y = z.y * z.y;
			c2.x = z.x * z.x;
			if ((c2.y + c2.x) > 4.0)
				break;
			z.y = 2.0 * z.x * z.y + f.y_im;
			z.x = c2.x - c2.y + f.x_re;
		}
		*(img_ptr + (g.x + g.y * 1920)) = n * 0x00111111;
		c.y -= fact.y;
	}
}

__kernel void mandelbrot(fract_t f,
						 double2 fact,
						 __constant __read_only uint *cset,
						 __global __write_only uint *img_ptr)
{
	double2	c;
	double2	c2;
	uint2	g;
	uint	n;

	g.x = get_global_id(0);
	c.x = (f.min_re + g.x * fact.x);
	c.y = f.max_im;
	for (g.y = 0; g.y < IMAGEHEIGHT; g.y++)
	{
		double2 z = {c.x, c.y};
		for (n = 0; n < f.iteration; n++)
		{
			c2.y = z.y * z.y;
			c2.x = z.x * z.x;
			if ((c2.y + c2.x) > 4.0)
				break;
			z.y = 2.0 * z.x * z.y + c.y;
			z.x = c2.x - c2.y + c.x;
		}
		*(img_ptr + (g.x + g.y * IMAGEWIDTH)) = n * 0x00111111;
		c.y -= fact.y;
	}
}

__kernel void multibrot(fract_t f,
						double2 fact,
						__constant __read_only uint *cset,
						__global __write_only uint *img_ptr)
{
	double2	c;
	double2	c2;
	uint2	g;
	uint	n;

	g.x = get_global_id(0);
	c.x = (f.min_re + g.x * fact.x);
	c.y = f.max_im;
	for (g.y = 0; g.y < IMAGEHEIGHT; g.y++)
	{
		double2 z = {c.x, c.y};
		for (n = 0; n < f.iteration; n++)
		{
			double tmp = atan2(z.y, z.x) * f.x_re;
			c2.y = z.y * z.y;
			c2.x = z.x * z.x;
			if ((c2.y + c2.x) > 4.0)
				break;
			z.y = pow((c2.x + c2.y), (f.x_re/2.0)) * sin(tmp) + c.y;
			z.x = pow((c2.x + c2.y), (f.x_re/2.0)) * cos(tmp) + c.x;
		}
		*(img_ptr + (g.x + g.y * IMAGEWIDTH)) = n * 0x00111111;
		c.y -= fact.y;
	}
}

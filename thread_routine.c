/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 04:20:22 by jye               #+#    #+#             */
/*   Updated: 2018/01/05 04:47:45 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <signal.h>
#include <pthread.h>
#include <stddef.h>

#define THREAD_MAX 18

static void	*draw_routine(void *param)
{
	static unsigned int	frac = IMAGEHEIGHT / THREAD_MAX;
	static uint64_t		tid;
	unsigned int		y;
	unsigned int		n;

	y = (tid++ % THREAD_MAX) * frac;
	n = y + frac;
	draw_nfract((t_mlx *)*((void **)(param)),
				(t_fract *)*((void **)(param + sizeof(void *))),
				y, n);
	pthread_exit(NULL);
	return (0);
}

int			init_draw_routine(t_mlx *mlx, t_fract *f)
{
	void		*param[2];
	pthread_t	tid[THREAD_MAX];
	int			i;

	param[0] = mlx;
	param[1] = f;
	i = 0;
	while (i < THREAD_MAX)
	{
		if (pthread_create(tid + i, NULL, draw_routine, param))
		{
			while (i--)
				pthread_kill(tid[i], SIGKILL);
			return (1);
		}
		++i;
	}
	while (i--)
		pthread_join(tid[i], NULL);
	return (0);
}

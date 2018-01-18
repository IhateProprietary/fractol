/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 08:40:02 by jye               #+#    #+#             */
/*   Updated: 2018/01/17 08:48:30 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <stdlib.h>

int		get_color(char **costr)
{
	char		*c;
	char		*s;
	t_mlxcolor	col;

	s = *costr;
	if (*s == 0)
		return (-1);
	col.color__ = 0;
	while (*s && (c = ft_strchr("rgb", *s)))
	{
		if (*++s == 0)
			break ;
		if (*c == 'r')
			col.color.r = ft_atoi(s);
		else if (*c == 'g')
			col.color.g = ft_atoi(s);
		else if (*c == 'b')
			col.color.b = ft_atoi(s);
		while (*s >= 0x30 && *s <= 0x39)
			s++;
	}
	if (*s != ';' && *s != 0)
		return (-1);
	*costr = s + 1;
	return (col.color__);
}

size_t	get_csetsize(char *s)
{
	char	*ptr;
	size_t	cssize;

	cssize = 0;
	while ((ptr = ft_strchr(s, ';')))
	{
		s = ptr + 1;
		cssize += 1;
		if (ptr == 0)
			break ;
	}
	return (cssize);
}

int		parse_color(t_fract *f)
{
	char		*s;
	t_mlxcolor	*set;
	size_t		i;
	int			ret;

	if ((s = f->color) == 0 || *s == 0)
		return (0);
	f->csetsize = get_csetsize(s);
	if ((set = (t_mlxcolor *)malloc(sizeof(t_mlxcolor) * f->csetsize)) == 0)
		return (1);
	i = 0;
	s = f->color;
	while (i < f->csetsize)
	{
		if ((ret = get_color(&s)) == -1)
		{
			free(set);
			return (1);
		}
		set[i++].color__ = ret;
	}
	f->set = set;
	return (0);
}

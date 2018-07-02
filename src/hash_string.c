/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 01:20:58 by jye               #+#    #+#             */
/*   Updated: 2018/02/04 01:42:32 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stddef.h>

uint64_t	hash_string(char *string)
{
	uint64_t	khash;

	khash = 0;
	while (*string)
	{
		khash *= 281474976710677;
		khash ^= *string | ((*string << 16) << 16);
		string++;
	}
	return (khash);
}

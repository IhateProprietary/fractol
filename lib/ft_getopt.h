/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 02:25:58 by jye               #+#    #+#             */
/*   Updated: 2018/02/03 02:29:41 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETOPT_H
# define FT_GETOPT_H
# define DEF_TYPE(t) t
# define DEF_NAME(n) n
# define DEF_VAL(v) v
# define DEF_(t, n) DEF_TYPE(t) DEF_NAME(n)
# define EXT_ACCESS extern
# define TYPE_INT int
# define TYPE_PTR char *
# define OPT_(t, name, val) DEF_(t, name) = DEF_VAL(val)
# if defined(MACRO_DECLARE)
#  define OPTIND_ OPT_(TYPE_INT, optind_, 0)
#  define OPTARG_ OPT_(TYPE_PTR, optarg_, 0)
#  define OPTERR_ OPT_(TYPE_INT, opterr_, 1)
# else
#  define OPTIND_ EXT_ACCESS DEF_(TYPE_INT, optind_)
#  define OPTARG_ EXT_ACCESS DEF_(TYPE_PTR, optarg_)
#  define OPTERR_ EXT_ACCESS DEF_(TYPE_INT, opterr_)
# endif

OPTIND_;
OPTARG_;
OPTERR_;
#endif

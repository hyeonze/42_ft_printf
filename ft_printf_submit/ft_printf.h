/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:56:40 by hann              #+#    #+#             */
/*   Updated: 2020/10/12 16:52:21 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_tags
{
	char	flag;
	int		width;
	int		dot;
	int		pre;
	int		signal;
}				t_tags;

int				ft_printf(const char *input, ...);
int				ft_parse_tag(const char *input, int i, t_tags *tags, \
		va_list ap);
int				ft_parse_type(char c, t_tags tags, va_list ap);

int				chk_flag(char c, t_tags **tags);
int				chk_width(char c, t_tags **tags, va_list ap);
int				chk_dot(char c, t_tags **tags);
int				chk_precision(char c, t_tags **tags, va_list ap);

int				parse_type_pct(t_tags tags);
int				parse_type_c(t_tags tags, va_list ap);
int				parse_type_s(t_tags tags, va_list ap);

int				parse_type_p(char c, t_tags tags, va_list ap);
int				parse_type_di(char c, t_tags tags, va_list ap);
int				parse_type_ux(char c, t_tags tags, va_list ap);

size_t			ft_strlen(const char *s);
int				ft_isdigit(int c);

int				ft_putchar(char c);
int				ft_is_type(char c);

t_tags			ft_init_tags(void);
int				converted_len(long long n, int base_num);
void			make_nbr_base(char c, va_list ap, long long *nbr, char **base);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:55:18 by hann              #+#    #+#             */
/*   Updated: 2020/10/12 16:52:21 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_parse_type(char c, t_tags tags, va_list ap)
{
	int		ret;

	ret = 0;
	if (c == '%')
		ret = parse_type_pct(tags);
	else if (c == 'c')
		ret = parse_type_c(tags, ap);
	else if (c == 's')
		ret = parse_type_s(tags, ap);
	else if (c == 'p')
		ret = parse_type_p(c, tags, ap);
	else if (c == 'd' || c == 'i')
		ret = parse_type_di(c, tags, ap);
	else if (c == 'u' || c == 'x' || c == 'X')
		ret = parse_type_ux(c, tags, ap);
	else
		return (-1);
	return (ret);
}

int		ft_parse_tag(const char *input, int i, t_tags *tags, va_list ap)
{
	while (input[i])
	{
		if (ft_is_type(input[i]))
			break ;
		if (chk_flag(input[i], &tags))
			i++;
		else if (chk_width(input[i], &tags, ap))
			i++;
		else if (chk_dot(input[i], &tags))
			i++;
		else if (chk_precision(input[i], &tags, ap))
			i++;
		else
			return (-1);
	}
	if (tags->signal == 1)
		tags->pre = 0;
	if (input[i] != '%' && input[i] != 's' && input[i] != 'c'
			&& tags->flag == '0' && tags->pre >= 0)
		tags->flag = '\0';
	return (i);
}

int		ft_printf(const char *input, ...)
{
	va_list	ap;
	int		i;
	int		cnt;
	t_tags	tags;

	va_start(ap, input);
	i = 0;
	cnt = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '%' && input[i + 1])
		{
			tags = ft_init_tags();
			i = ft_parse_tag(input, ++i, &tags, ap);
			cnt += ft_parse_type(input[i], tags, ap);
		}
		else
			cnt += ft_putchar(input[i]);
		if (i == -1 || cnt == -1)
			break ;
		i++;
	}
	va_end(ap);
	return (cnt);
}

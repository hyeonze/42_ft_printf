/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:55:03 by hann              #+#    #+#             */
/*   Updated: 2020/10/27 00:37:06 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_type_s(t_tags tags, va_list ap)
{
	int		cnt;
	int		i;
	int		output_cnt;
	char	*s;

	cnt = 0;
	s = va_arg(ap, char *);
	if (s == NULL)
		s = "(null)";
	if (tags.pre == -1)
		output_cnt = (int)ft_strlen(s);
	else
	{
		if (tags.pre > (int)ft_strlen(s))
			output_cnt = ft_strlen(s);
		else
			output_cnt = tags.pre;
	}
	i = tags.width - output_cnt;
	while (tags.flag == '\0' && i-- > 0)
		cnt += ft_putchar(' ');
	while (tags.flag == '0' && i-- > 0)
		cnt += ft_putchar('0');
	if (tags.dot == 1 && tags.pre == 0)
		;
	else
		cnt += write(1, s, output_cnt);
	while (tags.flag == '-' && i-- > 0)
		cnt += ft_putchar(' ');
	return (cnt);
}

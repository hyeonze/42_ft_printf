/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <                       >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:57:37 by                   #+#    #+#             */
/*   Updated: 2020/10/17 17:57:37 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_type_c(t_tags tags, va_list ap)
{
	int		cnt;
	int		i;
	char	c;

	cnt = 0;
	i = tags.width - 1;
	c = (char)va_arg(ap, int);
	while (tags.flag != '-' && i-- > 0)
		cnt += ft_putchar(' ');
	cnt += ft_putchar(c);
	while (tags.flag == '-' && i-- > 0)
		cnt += ft_putchar(' ');
	return (cnt);
}

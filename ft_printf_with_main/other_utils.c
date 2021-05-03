/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <                       >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:55:42 by                   #+#    #+#             */
/*   Updated: 2020/10/12 16:35:59 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int		ft_is_type(char c)
{
	if ((c == 'c') || (c == 's') || (c == 'p') || (c == 'd') || (c == 'i')
			|| (c == 'u') || (c == 'x') || (c == 'X') || (c == '%'))
		return (1);
	return (0);
}

t_tags	ft_init_tags(void)
{
	t_tags tags;

	tags.flag = '\0';
	tags.width = 0;
	tags.dot = 0;
	tags.pre = -1;
	tags.signal = 0;
	return (tags);
}

int		converted_len(long long n, int base_num)
{
	int		len;

	len = 0;
	if (n < 0)
	{
		n = n * (-1);
		len = len + 1;
	}
	if (n == 0)
		len = len + 1;
	while (n > 0)
	{
		n = n / base_num;
		len++;
	}
	return (len);
}

void	make_nbr_base(char c, va_list ap, long long *nbr, char **base)
{
	if (c == 'd' || c == 'i')
		*nbr = va_arg(ap, int);
	else if (c == 'u' || c == 'x' || c == 'X')
		*nbr = va_arg(ap, unsigned int);
	else if (c == 'p')
		*nbr = va_arg(ap, unsigned long);
	if (c == 'd' || c == 'i' || c == 'u')
		*base = "0123456789";
	else if (c == 'x' || c == 'p')
		*base = "0123456789abcdef";
	else if (c == 'X')
		*base = "0123456789ABCDEF";
}

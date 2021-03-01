/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_ux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:58:12 by hann              #+#    #+#             */
/*   Updated: 2020/10/27 00:30:30 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putnbr_base_ux(long long nbr, char *base, int *cnt, t_tags tags)
{
	int			number_system;

	if (nbr == 0 && tags.dot == 1 && tags.pre == 0)
	{
		if (tags.width >= 1)
			*cnt += ft_putchar(' ');
		return ;
	}
	number_system = (int)ft_strlen(base);
	if (nbr >= number_system)
		putnbr_base_ux(nbr / number_system, base, cnt, tags);
	*cnt += ft_putchar(base[nbr % number_system]);
}

int		print_inside_ux(t_tags tags, int len)
{
	int			i;
	int			cnt;

	cnt = 0;
	i = tags.pre - len;
	while (i-- > 0)
		cnt += ft_putchar('0');
	return (cnt);
}

int		print_outside_ux(t_tags tags, int len, char mode)
{
	int			i;
	int			arg;
	int			cnt;

	cnt = 0;
	if (len < tags.pre)
		arg = tags.pre;
	else
		arg = len;
	i = tags.width - arg;
	while (mode == ' ' && i-- > 0)
		cnt += ft_putchar(' ');
	while (mode == '0' && i-- > 0)
		cnt += ft_putchar('0');
	return (cnt);
}

int		parse_type_ux(char c, t_tags tags, va_list ap)
{
	long long	nbr;
	char		*base;
	int			cnt;
	int			len;

	cnt = 0;
	make_nbr_base(c, ap, &nbr, &base);
	len = converted_len(nbr, (int)ft_strlen(base));
	if (tags.flag == '\0' || (tags.flag == '0' && tags.pre > 0))
		cnt += print_outside_ux(tags, len, ' ');
	if (tags.flag == '0' && (tags.pre == 0 || tags.pre == -1))
		cnt += print_outside_ux(tags, len, '0');
	cnt += print_inside_ux(tags, len);
	putnbr_base_ux(nbr, base, &cnt, tags);
	if (tags.flag == '-')
		cnt += print_outside_ux(tags, len, ' ');
	return (cnt);
}

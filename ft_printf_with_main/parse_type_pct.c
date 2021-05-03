/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_pct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <                       >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:56:39 by                   #+#    #+#             */
/*   Updated: 2020/10/17 17:56:43 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_type_pct(t_tags tags)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = tags.width - 1;
	while (tags.flag == '\0' && i-- > 0)
		cnt += ft_putchar(' ');
	while (tags.flag == '0' && i-- > 0)
		cnt += ft_putchar('0');
	cnt += ft_putchar('%');
	while (tags.flag == '-' && i-- > 0)
		cnt += ft_putchar(' ');
	return (cnt);
}

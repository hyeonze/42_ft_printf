/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:55:50 by hann              #+#    #+#             */
/*   Updated: 2020/10/27 00:35:55 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	chk_flag(char c, t_tags **tags)
{
	if ((*tags)->flag != '-' && (c == '0' || c == '-')
			&& (*tags)->width == 0 && (*tags)->dot == 0)
	{
		(*tags)->flag = c;
		return (1);
	}
	else if ((c == '0' || c == '-') && (*tags)->width == 0 && (*tags)->dot == 0)
		return (1);
	return (0);
}

int	chk_width(char c, t_tags **tags, va_list ap)
{
	int	ret;

	ret = 1;
	if (ft_isdigit(c) && (*tags)->dot == 0)
	{
		(*tags)->width = ((*tags)->width * 10) + (c - '0');
		if ((*tags)->width < 0)
			(*tags)->width *= -1;
	}
	else if (c == '*' && (*tags)->dot == 0)
	{
		(*tags)->width = va_arg(ap, int);
		if ((*tags)->width < 0)
		{
			(*tags)->width = (*tags)->width * (-1);
			(*tags)->flag = '-';
		}
	}
	else
		ret = 0;
	return (ret);
}

int	chk_dot(char c, t_tags **tags)
{
	if (c == '.')
	{
		(*tags)->dot = 1;
		(*tags)->pre = 0;
		return (1);
	}
	return (0);
}

int	chk_precision(char c, t_tags **tags, va_list ap)
{
	int	ret;

	ret = 1;
	if (c == '-' && (*tags)->dot == 1)
		(*tags)->signal = 1;
	else if (ft_isdigit(c) && (*tags)->dot == 1)
	{
		(*tags)->pre = ((*tags)->pre * 10) + (c - '0');
		if ((*tags)->signal == 1)
		{
			(*tags)->flag = '-';
			(*tags)->width = (*tags)->pre;
		}
	}
	else if (c == '*' && (*tags)->dot == 1)
	{
		(*tags)->pre = va_arg(ap, int);
		if ((*tags)->pre < 0)
			(*tags)->pre = -1;
	}
	else
		ret = 0;
	return (ret);
}

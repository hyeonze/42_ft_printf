/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:55:18 by hann              #+#    #+#             */
/*   Updated: 2020/10/25 16:13:47 by hann             ###   ########.fr       */
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
		if (ft_is_type(input[i])) // 형식지정자면 break
			break ;
		if (chk_flag(input[i], &tags)) // input[i]가 '0' 또는 '-'일 경우(둘 다 왔을 경우 '-'만 처리)
			i++;
		else if (chk_width(input[i], &tags, ap)) // '.' 안만난 상태에서 input이 숫자거나 *일 경우 tags.width 저장
			i++;
		else if (chk_dot(input[i], &tags)) // input[i]가 '.'일 경우 tags.dot을 1로, tags.pre를 0으로
			i++;
		else if (chk_precision(input[i], &tags, ap)) // input[i]가 '.'만난 후 숫자거나 *일 경우 tags.pre 저장
			i++;
		else
			return (-1);
	}
	if (tags->signal == 1) // '.'이후 '-'만난 경우(.숫-, 언디파인드)
		tags->pre = 0; // tags.pre를 0으로(-앞에 들어갔던 정밀도무시하고 tags.pre를 0으로, 숫자는 정밀도무시, 문자는 출력안함)
	if (input[i] != '%' && input[i] != 's' && input[i] != 'c'
			&& tags->flag == '0' && tags->pre >= 0) // input[i]가 '%', 's', 'c'가 아니고(d, u, x, p), 정밀도가 있을 경우 '0'플래그 무시
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

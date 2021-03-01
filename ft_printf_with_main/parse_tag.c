/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 15:55:50 by hann              #+#    #+#             */
/*   Updated: 2020/10/14 17:37:19 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	chk_flag(char c, t_tags **tags)
{
	if ((*tags)->flag != '-' && (c == '0' || c == '-')
			&& (*tags)->width == 0 && (*tags)->dot == 0) // '-', 폭, '.' 만난 적이 없는 상태에서 c가 '0'또는 '-'이면 이를 tags.flag에 저장 후 1반환('-', '0', '0-' 처리, '0-'의 경우 '-'만 처리)
	{
		(*tags)->flag = c;
		return (1);
	}
	else if ((c == '0' || c == '-') && (*tags)->width == 0 && (*tags)->dot == 0) // 폭, '.' 만난 적이 없는 상태에서 tags.flag가 '-'이고 c가 '0'또는 '-'이면 1반환('-0'순으로 들어왔을 때 '0' 무시하고 '-'처리)
		return (1);
	return (0);
}

int	chk_width(char c, t_tags **tags, va_list ap)
{
	int	ret;

	ret = 1;
	if (ft_isdigit(c) && (*tags)->dot == 0) // '.'안만난 상태에서 c가 숫자라면
	{
		(*tags)->width = ((*tags)->width * 10) + (c - '0'); // tags.width에 c 연결해서 저장
        if ((*tags)->width < 0) // tags.width가 음수라면
            (*tags)->width *= -1; // 부호변경
	}
	else if (c == '*' && (*tags)->dot == 0) // '.'안만난 상태에서 c가 *인 경우 
	{
		(*tags)->width = va_arg(ap, int); // 가변인자 받아와서 tags.width에 저장
		if ((*tags)->width < 0) // tags.width가 음수라면
		{
			(*tags)->width = (*tags)->width * (-1); // 부호변경
			(*tags)->flag = '-'; // tags.flag를 '-'로
		}
	}
	else
		ret = 0;
	return (ret);
}

int	chk_dot(char c, t_tags **tags)
{
	if (c == '.') // c가 '.'일 경우
	{
		(*tags)->dot = 1; // tags.dot을 1로
		(*tags)->pre = 0; // tags.pre를 0으로
		return (1);
	}
	return (0);
}

int	chk_precision(char c, t_tags **tags, va_list ap)
{
	int	ret;

	ret = 1;
	if (c == '-' && (*tags)->dot == 1) // '.' 만난 후 c가 '-'라면
		(*tags)->signal = 1; // tags.signal을 1로
	else if (ft_isdigit(c) && (*tags)->dot == 1) // '.'을 만난 후 c가 숫자인 경우
	{
		(*tags)->pre = ((*tags)->pre * 10) + (c - '0'); // tags.pre에 c 누적해서 저장
		if ((*tags)->signal == 1) // tags.signal이 1이라면(.-숫)
		{
			(*tags)->flag = '-'; // tags.flag에 '-'저장
			(*tags)->width = (*tags)->pre; // tags.width에 tags.pre저장(언디파인드이지만 이렇게 출력해줌)
		}
	}
	else if (c == '*' && (*tags)->dot == 1) // '.'만난 후 c가 *인 경우
	{
		(*tags)->pre = va_arg(ap, int); // tags.pre에 가변인자 저장
		if ((*tags)->pre < 0) // tags.pre가 음수라면
			(*tags)->pre = -1; // 입력한 정밀도 무시
	}
	else
		ret = 0;
	return (ret);
}

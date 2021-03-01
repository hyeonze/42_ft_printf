/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:56:49 by hann              #+#    #+#             */
/*   Updated: 2020/10/18 00:41:29 by hann             ###   ########.fr       */
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
	if (s == NULL) // s가 NULL일 경우
		s = "(null)"; // s에 "(null)"저장
	if (tags.pre == -1) // 정밀도 없다면 output_cnt에 s길이 저장
		output_cnt = (int)ft_strlen(s);
    else // 정밀도 있을 경우
    {
        if (tags.pre > (int)ft_strlen(s)) // 정밀도>글자수면
            output_cnt = ft_strlen(s); // output_cnt에 s길이 저장(정밀도 무시, 글자수만)
        else // 정밀도<=글자수면
            output_cnt = tags.pre; // output_cnt에 정밀도저장(정밀도만 적용)
    }
	i = tags.width - output_cnt; // 폭에서 글자수 빼서 i에 저장(폭<글자수면 폭 무시되게)
	while (tags.flag == '\0' && i-- > 0) // 플래그 '\0'이면 ' '출력(i만큼)
		cnt += ft_putchar(' ');
	while (tags.flag == '0' && i-- > 0) // 플래그 '0'이면 '0'출력(i만큼)
		cnt += ft_putchar('0');
	if (tags.dot == 1 && tags.pre == 0) // .이후 숫자아닌거 만났거나 ".숫-"인 경우('s'출력안함)
		;
	else // output_cnt만큼 's'출력
		cnt += write(1, s, output_cnt);
	while (tags.flag == '-' && i-- > 0) // 플래그 '-'이면 ' '출력(i만큼)
		cnt += ft_putchar(' ');
	return (cnt); // 출력한글자수 cnt에 저장됨, 반환
}

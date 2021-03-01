/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_ux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hann <hann@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:57:03 by hann              #+#    #+#             */
/*   Updated: 2020/10/25 16:29:30 by hann             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putnbr_base_ux(long long nbr, char *base, int *cnt, t_tags tags)
{
	int			number_system;

	if (nbr == 0 && tags.dot == 1 && tags.pre == 0) // 인자가 0인데 정밀도가 0이거나 없는(.만있는)경우
	{
		if (tags.width >= 1)
			*cnt += ft_putchar(' ');
		return ; // 폭이 있다면 공백 출력하고 그렇지 않으면 출력하지 않음, 반환
	}
	number_system = (int)ft_strlen(base); // n_s = 베이스길이
	if (nbr >= number_system) // 재귀로 nbr출력
		putnbr_base_ux(nbr / number_system, base, cnt, tags);
	*cnt += ft_putchar(base[nbr % number_system]);
}

int		print_inside_ux(t_tags tags, int len) // 정밀도 > 글자수 이면 차이만큼 '0'출력
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
	if (len < tags.pre) // 정밀도 > 글자수 면 정밀도와 글자수 다 준수
		arg = tags.pre;
	else // 정밀도(부호있을경우 +1) <= 글자수 면 정밀도 무시
		arg = len;
	i = tags.width - arg; // 폭이 제일 큰 수 아니면 폭 무시, 제일 큰 수이면 i개만큼 mode출력
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
	make_nbr_base(c, ap, &nbr, &base); // nbr을 가변인자로 채우고, base를 'c'에 맞는걸로 채워줌
	len = converted_len(nbr, (int)ft_strlen(base)); // len에 진법 바꿨을 때 자릿수 측정해서 저장
	if (tags.flag == '\0' || (tags.flag == '0' && tags.pre > 0)) // 플래그가 없거나 || 0플래그와 정밀도가 있을 경우(정밀도 있으면 0플래그 무시하기 때문에 폭 출력)
		cnt += print_outside_ux(tags, len, ' '); // 폭 출력
	if (tags.flag == '0' && (tags.pre == 0 || tags.pre == -1)) // 플래그가 0이고 정밀도가 없거나 0일 경우(정밀도 있으면 0플래그 무시)
		cnt += print_outside_ux(tags, len, '0'); // 폭을 0으로 채워 출력
	cnt += print_inside_ux(tags, len); // 정밀도 출력
	putnbr_base_ux(nbr, base, &cnt, tags); // nbr출력
	if (tags.flag == '-') // '-'플래그 있을 경우
		cnt += print_outside_ux(tags, len, ' '); // 폭 출력
	return (cnt);
}

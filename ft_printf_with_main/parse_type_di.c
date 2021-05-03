/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_di.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <                       >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:57:46 by                   #+#    #+#             */
/*   Updated: 2020/10/26 22:19:08 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	putnbr_base_di(long long nbr, char *base, int *cnt, t_tags tags)
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
		putnbr_base_di(nbr / number_system, base, cnt, tags);
	*cnt += ft_putchar(base[nbr % number_system]);
}

int		print_inside_di(t_tags tags, int len, int minus)
{
	int			i;
	int			cnt;

	cnt = 0;
	i = (tags.pre + minus) - len; // 정밀도(부호있을경우 +1) > 글자수 일 경우
	while (i-- > 0) // i번만큼 '0'출력
		cnt += ft_putchar('0');
	return (cnt);
}

int		print_outside_di(t_tags tags, int len, int minus, char mode)
{
	int			i;
	int			arg;
	int			cnt;

	cnt = 0;
	if(len < (tags.pre + minus)) // 정밀도(부호있을경우 +1) > 글자수 면 정밀도와 글자수 다 준수, 부호가 폭 한 칸차지
		arg = tags.pre + minus;
	else // 정밀도(부호있을경우 +1) <= 글자수 면 정밀도 무시
		arg = len;
	i = tags.width - arg; // 폭이 제일 큰 수 아니면 폭 무시, 제일 큰 수이면 i개만큼 mode출력
	while (mode == ' ' && i-- > 0)
		cnt += ft_putchar(' ');
	while (mode == '0' && i-- > 0)
		cnt += ft_putchar('0');
	return (cnt);
}

int		parse_type_di(char c, t_tags tags, va_list ap)
{
	long long	nbr;
	char		*base;
	int			cnt;
	int			len;
	int			minus;

	cnt = 0;
	make_nbr_base(c, ap, &nbr, &base); // nbr에 가변인자 저장, base에 진법저장
	if (nbr < 0) // nbr이 음수일 경우 minus를 1로
		minus = 1;
	else // nbr이 양수거나 0이면 minus를 0으로
		minus = 0;
	len = converted_len(nbr, (int)ft_strlen(base)); // len에 출력했을 때 인자자릿수 저장
	if (tags.flag == '\0' || (tags.flag == '0' && tags.pre > 0)) // 플래그가 없거나 || 0플래그와 정밀도가 있을 경우(정밀도 있으면 0플래그 무시하기 때문에 폭 출력)
		cnt += print_outside_di(tags, len, minus, ' '); // 폭 출력
	if (minus == 1) // 부호 있을 경우 '-'출력
		cnt += ft_putchar('-');
	if (tags.flag == '0' && (tags.pre == 0 || tags.pre == -1)) // 플래그가 0이고 정밀도가 없거나 0일 경우(정밀도 있으면 0플래그 무시)
		cnt += print_outside_di(tags, len, minus, '0'); // 폭을 0으로 채워 출력
	cnt += print_inside_di(tags, len, minus); // 정밀도 출력
	if (nbr < 0) // nbr이 음수일 경우
		putnbr_base_di(-nbr, base, &cnt, tags); // nbr출력
	else // nbr이 양수일 경우
		putnbr_base_di(nbr, base, &cnt, tags); // nbr출력
	if (tags.flag == '-') // '-'플래그 있을 경우
		cnt += print_outside_di(tags, len, minus, ' '); // 폭 출력
	return (cnt);
}
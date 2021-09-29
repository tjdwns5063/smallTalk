/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 13:35:08 by seongjki          #+#    #+#             */
/*   Updated: 2021/07/05 12:20:58 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	decide_num(char *str, int cnt)
{
	char	*tmp;
	int		num;

	tmp = (char *)malloc(sizeof(char) * (cnt + 1));
	ft_strlcpy(tmp, str + 1, (cnt + 1));
	num = ft_atoi((const char *)tmp);
	free(tmp);
	return (num);
}

static int	meet_asterisk(char **str, char *ptr, va_list ap)
{
	int		num;

	num = va_arg(ap, int);
	*str = ptr;
	return (num);
}

int	check_width(char **str, va_list ap)
{
	int		num;
	char	*ptr;
	int		cnt;

	cnt = 0;
	ptr = (*str + 1);
	num = 0;
	if (*ptr == '*')
		return (meet_asterisk(str, ptr, ap));
	while (*ptr && (ft_isdigit(*ptr) || *ptr == '-'))
	{
		ptr++;
		cnt++;
	}
	if (cnt > 0)
	{
		num = decide_num(*str, cnt);
		*str = *str + cnt;
	}
	return (num);
}

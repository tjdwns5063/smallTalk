/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 16:05:27 by seongjki          #+#    #+#             */
/*   Updated: 2021/07/05 12:13:51 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_flag(char **str)
{
	int		ret;
	int		m_cnt;

	ret = 0;
	m_cnt = 0;
	while (*(*str + 1) == '0' || *(*str + 1) == '-' || *(*str + 1) == ' ')
	{
		*str = (*str + 1);
		if (**str == '0')
			ret = '0';
		if (**str == '-')
			m_cnt++;
	}
	if (m_cnt > 0)
		ret = '-';
	return (ret);
}

int	check_precision(char **str)
{
	if (*(*str + 1) == '.')
	{
		*str = (*str + 1);
		return ('.');
	}
	return (0);
}

int	check_type(char **str)
{
	char	c;

	if (ft_isalpha(*(*str + 1)) || *(*str + 1) == '%')
	{
		*str = (*str + 1);
		c = **str;
		return (c);
	}
	return (0);
}

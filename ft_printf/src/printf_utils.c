/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:35:37 by seongjki          #+#    #+#             */
/*   Updated: 2021/06/30 21:51:25 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_str(char *str)
{
	while (*str)
	{
		write(1, &(*str), 1);
		str++;
	}
}

void	fill_width(t_info info, char **out)
{
	int		idx;

	idx = 0;
	while (idx < info.size)
	{
		if (info.flag == '0')
			(*out)[idx] = '0';
		else
			(*out)[idx] = ' ';
		idx++;
	}
}

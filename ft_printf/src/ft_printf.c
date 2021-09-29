/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:24:03 by seongjki          #+#    #+#             */
/*   Updated: 2021/07/05 12:19:38 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_info(char **str, t_info *info, va_list ap)
{
	info->flag = check_flag(str);
	info->width = check_width(str, ap);
	info->precision = check_precision(str);
	info->precision_size = check_width(str, ap);
	info->type = check_type(str);
	info->negative = 0;
	info->size = 0;
	if (info->precision_size < 0)
	{
		info->precision = 0;
		info->precision_size = 0;
	}
	if ((info->precision == '.' && info->precision_size >= 0)
		&& info->flag == '0')
	{
		if (info->type != 'c' && info->type != '%')
			info->flag = 0;
	}
	if (info->width < 0)
	{
		info->flag = '-';
		info->width *= -1;
	}
}

static int	seperate_type(char **str, t_info *info, va_list ap)
{
	int		type;
	int		ret;

	type = info->type;
	ret = 0;
	if (type == 'd' || type == 'i' || type == 'u'
		|| type == 'x' || type == 'X')
		ret = print_d(info, ap);
	else if (type == 'c' || type == '%')
		ret = print_c(info, ap);
	else if (type == 's')
		ret = print_s(info, ap);
	else if (type == 'p')
		ret = print_p(info, ap);
	else
		ret = print_invalid_type(info, info->type);
	(*str)++;
	return (ret);
}

static int	check_string(char **str, va_list ap)
{
	t_info		info;
	int			ret;
	int			parse_ret;

	ret = 0;
	while (**str)
	{
		if (**str == '%')
		{
			check_info(str, &info, ap);
			parse_ret = seperate_type(str, &info, ap);
			if (parse_ret == -1)
				return (-1);
			ret += parse_ret;
		}
		else
		{
			ret += write(1, &(**str), 1);
			(*str)++;
		}
	}
	return (ret);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	char		*ptr;
	t_info		info;
	int			res;

	ptr = (char *)str;
	va_start(ap, str);
	res = check_string(&ptr, ap);
	va_end(ap);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:42:02 by seongjki          #+#    #+#             */
/*   Updated: 2021/07/05 12:17:07 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_size(char *tmp, t_info info, int value)
{
	int		size;

	size = ft_strlen(tmp);
	if (info.precision_size > size - (info.negative == 'n'))
		size = info.precision_size + (info.negative == 'n');
	if (info.width > size)
		size = info.width;
	if (info.width == 0 && info.precision == '.' && info.precision_size == 0
		&& value == 0)
		size = 0;
	return (size);
}

static void	apply_precision(t_info info, char **out, char *tmp)
{
	int		idx;
	int		cnt;
	int		len;

	len = ft_strlen(tmp);
	idx = info.size - 1;
	if (info.flag == '-')
		idx = 0;
	cnt = info.precision_size + (info.negative == 'n');
	if (cnt < len)
		cnt = len;
	while (cnt--)
	{
		if (info.flag == '-')
			(*out)[idx++] = '0';
		else
			(*out)[idx--] = '0';
	}
}

static void	fill_arg(t_info info, char **out, char *tmp)
{
	int		idx;
	int		cnt;
	int		len;

	len = ft_strlen(tmp);
	idx = info.size - 1;
	cnt = len - (info.negative == 'n');
	while ((*out)[idx] == ' ')
		idx--;
	while (*tmp)
		tmp++;
	tmp--;
	while (cnt--)
		(*out)[idx--] = *tmp--;
	idx = 0;
	while ((*out)[idx] == ' ')
		idx++;
	if (info.negative == 'n')
		(*out)[idx] = '-';
}

char	*make_tmp(int value, t_info info)
{
	char	*tmp;

	tmp = ft_itoa(value);
	if (info.type == 'x')
		tmp = ft_xtoa(value);
	if (info.type == 'X')
		tmp = ft_upper_xtoa(value);
	if (info.type == 'u')
		tmp = ft_utoa(value);
	return (tmp);
}

int	print_d(t_info *info, va_list ap)
{
	char	*tmp;
	int		value;
	char	*out;

	value = va_arg(ap, int);
	tmp = make_tmp(value, *info);
	if ((info->type == 'd' || info->type == 'i') && value < 0)
		info->negative = 'n';
	info->size = get_size(tmp, *info, value);
	out = (char *)malloc(sizeof(char) * (info->size + 1));
	if (!out)
		return (-1);
	out[info->size] = '\0';
	fill_width(*info, &out);
	if (!(info->precision == '.' && info->precision_size == 0 && value == 0))
	{
		apply_precision(*info, &out, tmp);
		fill_arg(*info, &out, tmp);
	}
	print_str(out);
	free(tmp);
	free(out);
	return (info->size);
}

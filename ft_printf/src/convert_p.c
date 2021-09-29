/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:42:02 by seongjki          #+#    #+#             */
/*   Updated: 2021/07/05 12:18:27 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_size(char *tmp, t_info info, int value)
{
	int		size;

	size = ft_strlen(tmp) + 2;
	if (info.precision_size > size - 2)
		size = info.precision_size + 2;
	if (info.width > size)
		size = info.width;
	if (info.width <= 2 && info.precision == '.' && info.precision_size == 0
		&& value == 0)
		size--;
	return (size);
}

static void	apply_precision(t_info info, char **out, char *tmp)
{
	int		idx;
	int		cnt;
	int		len;

	len = ft_strlen(tmp) + 2;
	idx = info.size - 1;
	if (info.flag == '-')
		idx = 0;
	cnt = info.precision_size + 2;
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
	cnt = len;
	while ((*out)[idx] == ' ')
		idx--;
	while (*tmp)
		tmp++;
	tmp--;
	while (cnt--)
		(*out)[idx--] = *tmp--;
}

void	fill_prefix(char **out, long long value, t_info *info)
{
	int				idx;

	idx = 0;
	while ((*out)[idx] == ' ')
		idx++;
	if (info->precision == '.' && info->precision_size == 0 && value == 0)
	{
		if (info->flag == '-')
			idx = 0;
		else
			idx = info->size - 2;
	}
	(*out)[idx++] = '0';
	(*out)[idx++] = 'x';
}

int	print_p(t_info *info, va_list ap)
{
	char			*tmp;
	long long		value;
	char			*out;

	value = va_arg(ap, long long);
	tmp = ft_long_xtoa(value);
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
	fill_prefix(&out, value, info);
	print_str(out);
	free(tmp);
	free(out);
	return (info->size);
}

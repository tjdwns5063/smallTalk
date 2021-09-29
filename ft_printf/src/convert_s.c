/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:27:27 by seongjki          #+#    #+#             */
/*   Updated: 2021/07/05 12:19:01 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_size(char *tmp, t_info info)
{
	int		size;

	size = ft_strlen(tmp);
	if (info.width > size)
		size = info.width;
	return (size);
}

static void	fill_arg(t_info info, char **out, char *tmp)
{
	int		idx;
	int		cnt;

	idx = 0;
	cnt = ft_strlen(tmp);
	if (info.flag == '-')
	{
		while (cnt--)
			(*out)[idx++] = *tmp++;
	}
	else
	{
		while ((*out)[idx])
			idx++;
		idx--;
		while (*tmp)
			tmp++;
		tmp--;
		while (cnt--)
			(*out)[idx--] = *tmp--;
	}
}

static char	*apply_precision(va_list ap, t_info *info)
{
	char	*value;
	char	*ret;
	int		idx;
	int		len;

	value = va_arg(ap, char *);
	idx = -1;
	if (value == NULL)
		value = ft_strdup("(null)");
	len = ft_strlen(value);
	if (info->precision_size > len)
		info->precision_size = len;
	if (info->precision == '.')
	{
		ret = (char *)malloc(sizeof(char) * (info->precision_size + 1));
		ret[info->precision_size] = '\0';
		while (++idx < info->precision_size && value[idx])
			ret[idx] = value[idx];
	}
	else
		ret = ft_strdup(value);
	return (ret);
}

int	print_s(t_info *info, va_list ap)
{
	char	*tmp;
	char	*out;

	tmp = apply_precision(ap, info);
	info->size = get_size(tmp, *info);
	out = (char *)malloc(sizeof(char) * (info->size + 1));
	if (!out)
		return (-1);
	out[info->size] = '\0';
	fill_width(*info, &out);
	fill_arg(*info, &out, tmp);
	print_str(out);
	free(tmp);
	free(out);
	return (info->size);
}

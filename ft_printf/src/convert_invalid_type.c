/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_invalid_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 14:42:02 by seongjki          #+#    #+#             */
/*   Updated: 2021/07/05 12:17:36 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_size(t_info info)
{
	int		size;

	size = 1;
	if (info.width > size)
		size = info.width;
	return (size);
}

static void	fill_arg(t_info info, char **out, int value)
{
	int		idx;

	idx = info.size - 1;
	if (info.flag == '-')
		idx = 0;
	(*out)[idx] = value;
}

int	print_invalid_type(t_info *info, int value)
{
	char	*out;
	int		len;

	if (value == 0)
		return (0);
	info->size = get_size(*info);
	out = (char *)malloc(sizeof(char) * (info->size + 1));
	if (!out)
		return (-1);
	out[info->size] = '\0';
	fill_width(*info, &out);
	fill_arg(*info, &out, value);
	print_str(out);
	if (!value)
	{
		len = ft_strlen(out);
		ft_putchar_fd(out[len], 1);
		print_str(out + len + 1);
	}
	free(out);
	return (info->size);
}

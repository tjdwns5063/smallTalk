/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:36:18 by seongjki          #+#    #+#             */
/*   Updated: 2021/09/27 16:12:43 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*g_binary;

void	sighandler1(int signo)
{
	if (signo == 30)
	{
		*g_binary = '0';
		g_binary++;
	}
	else if (signo == 31)
	{
		*g_binary = '1';
		g_binary++;
	}
}

int	convert_decimal(char *str)
{
	int	idx;
	int	pow;
	int	ret;

	idx = 0;
	pow = 7;
	ret = 0;
	while (str[idx])
	{
		if (str[idx] == '1')
			ret += ft_pow(2, pow);
		idx++;
		pow--;
	}
	return (ret);
}

int	main(void)
{
	int		pid;
	int		cnt;
	char	*binary_ptr;
	int		word;

	pid = getpid();
	cnt = 0;
	g_binary = (char *)malloc(sizeof(char) * 9);
	binary_ptr = g_binary;
	ft_printf("%d\n", pid);
	while (1)
	{
		if (signal(SIGUSR1, sighandler1) || signal(SIGUSR2, sighandler1))
			cnt++;
		if (cnt == 8)
		{
			word = convert_decimal(binary_ptr);
			write(1, &word, 1);
			cnt = 0;
			g_binary = binary_ptr;
		}
		pause();
	}
	exit(0);
}

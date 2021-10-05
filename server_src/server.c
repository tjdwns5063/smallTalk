/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:36:18 by seongjki          #+#    #+#             */
/*   Updated: 2021/10/05 16:42:15 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	g_binary[9];

void	sighandler1(int signo)
{
	static int	idx;

	if (signo == 30)
	{
		g_binary[idx] = '0';
		idx++;
	}
	else if (signo == 31)
	{
		g_binary[idx] = '1';
		idx++;
	}
	if (idx >= 8)
		idx = 0;
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
	int		word;

	pid = getpid();
	cnt = 0;
	ft_printf("%d\n", pid);
	while (1)
	{
		if (signal(SIGUSR1, sighandler1) || signal(SIGUSR2, sighandler1))
			cnt++;
		if (cnt >= 8)
		{
			word = convert_decimal(g_binary);
			ft_printf("%c", word);
			cnt = 0;
		}
		pause();
	}
}

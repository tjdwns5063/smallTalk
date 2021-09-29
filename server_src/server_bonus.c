/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:36:18 by seongjki          #+#    #+#             */
/*   Updated: 2021/09/27 18:01:52 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

struct sigaction g_sig_strct;

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

void	sighandler1(int signo, siginfo_t *siginfo, void *context)
{
	static int	cnt;
	static char	str[9];
	int			word;
	int			cli_pid;

	(void) context;
	cli_pid = siginfo->si_pid;
	if (signo == 30)
		str[cnt++] = '0';
	else
		str[cnt++] = '1';
	if (cnt >= 8)
	{
		word = convert_decimal(str);
		write(1, &word, 1);
		cnt = 0;
		kill(cli_pid, SIGUSR1);
	}
}

int	main(void)
{
	int		pid;

	pid = getpid();
	ft_printf("[Server PID %d]\n", pid);
	g_sig_strct.sa_sigaction = sighandler1;
	while (1)
	{
		if (sigaction(SIGUSR1, &g_sig_strct, NULL) < 0 || sigaction(SIGUSR2, &g_sig_strct, NULL) < 0)
			ft_printf("Error!\n");
		pause();
	}
	exit(0);
}

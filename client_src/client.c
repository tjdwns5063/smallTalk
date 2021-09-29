/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongjki <seongjk@student.42seoul.k>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 15:14:03 by seongjki          #+#    #+#             */
/*   Updated: 2021/09/27 15:26:18 by seongjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	*make_binary(unsigned int num, char *base)
{
	char	*binary;
	int		idx;

	idx = 0;
	binary = (char *)malloc(sizeof(char) * 9);
	binary[8] = '\0';
	while (idx < 8)
		binary[idx++] = '0';
	idx = 7;
	while (idx >= 0)
	{
		binary[idx] = base[num % 2];
		num /= 2;
		idx--;
	}
	return (binary);
}

static void	send_signal(char *binary, int pid)
{
	while (*binary)
	{
		if (pid >= 101)
		{
			if (*binary == '0')
				kill(pid, SIGUSR1);
			else if (*binary == '1')
				kill(pid, SIGUSR2);
			else
				ft_printf("Error!\n");
		}
		else
			ft_printf("Invalid PID\n");
		usleep(50);
		binary++;
	}
}

static void	convert_binary(char *to_str, int pid)
{
	char	*binary;

	while (*to_str)
	{
		binary = make_binary(*to_str, "01");
		send_signal(binary, pid);
		free(binary);
		binary = 0;
		to_str++;
	}
	binary = make_binary('\n', "01");
	send_signal(binary, pid);
	free(binary);
}

int	main(int ac, char **av)
{
	char	*to_str;
	int		pid;

	if (ac < 3)
		ft_printf("Please, more argument!");
	else
	{
		pid = ft_atoi(av[1]);
		to_str = av[2];
		ft_printf("%s\n", to_str);
		convert_binary(to_str, pid);
	}
}

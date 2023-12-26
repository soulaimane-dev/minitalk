/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:29:17 by sbouabid          #+#    #+#             */
/*   Updated: 2023/12/11 16:41:25 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	byte_to_decimal(char *byte, int pid)
{
	int	result;
	int	i;

	result = 0;
	i = 7;
	while (i >= 0)
	{
		if (byte[i] == '1')
		{
			result += 1 << (7 - i);
		}
		i--;
	}
	if (result == '\0')
	{
		kill(pid, SIGUSR1);
	}
	ft_putchar(result);
}

static void	handler(int sgl, siginfo_t *info, void *test)
{
	static int	range;
	static int	nbr;
	static char	bit[8];

	(void)test;
	if (nbr != info->si_pid)
	{
		nbr = info->si_pid;
		range = 0;
	}
	if (range < 8)
	{
		if (sgl == SIGUSR1)
			bit[range] = '1';
		else
			bit[range] = '0';
		range++;
	}
	if (range == 8)
	{
		range = 0;
		byte_to_decimal(bit, info->si_pid);
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	ft_putstr("PID : ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
}

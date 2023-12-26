/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 12:01:35 by sbouabid          #+#    #+#             */
/*   Updated: 2023/12/11 16:41:21 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	byte_to_decimal(char *byte)
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
		byte_to_decimal(bit);
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

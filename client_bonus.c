/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 14:27:12 by sbouabid          #+#    #+#             */
/*   Updated: 2023/12/10 20:21:59 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	send_bit(int value, int pid)
{
	int	i;
	int	mask;

	mask = 1 << 7;
	i = 0;
	while (i < 8)
	{
		if (value & mask)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		mask = mask >> 1;
		usleep(800);
		i++;
	}
}

void	handler(int signal)
{
	(void)signal;
	ft_putstr("Vu :✓✓\n");
}

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	signal(SIGUSR1, handler);
	if (ac != 3)
		return (1);
	else
	{
		pid = ft_atoi(av[1]);
		if (pid <= 0)
			return (1);
		i = 0;
		while (av[2][i])
		{
			send_bit(av[2][i], pid);
			i++;
		}
		send_bit('\0', pid);
	}
	return (0);
}

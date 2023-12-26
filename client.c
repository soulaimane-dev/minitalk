/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouabid <sbouabid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:53:26 by sbouabid          #+#    #+#             */
/*   Updated: 2023/12/11 16:43:12 by sbouabid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_bit(int value, int pid)
{
	int	i;
	int	mask;

	mask = 0;
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

int	main(int ac, char **av)
{
	int	pid;
	int	i;

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
	}
	return (0);
}

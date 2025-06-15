/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:31:17 by cress             #+#    #+#             */
/*   Updated: 2025/06/15 19:19:50 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

void	sig_to_char(int sig)
{
	static char			c;
	static int		i;

	i = 0;
	c = '\0';
	if (sig == SIGUSR1)
	{
		c |= (1 << i);
		usleep(42);
	}
	else if (sig == SIGUSR2)
	{
		c |= (0 << i);
		usleep(42);
	}
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	__pid_t	pid;
	char	*s1;

	s1 = "I'm the server, my PID is";
	pid = getpid();
	ft_printf ("%s, %d\n", s1, pid);
	sleep(42);
	signal(SIGUSR1, sig_to_char);
	signal(SIGUSR2, sig_to_char);
	return (0);
}

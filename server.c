/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:31:17 by cress             #+#    #+#             */
/*   Updated: 2025/06/23 22:10:01 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

char g_str[4096];

void	wrt_str(__pid_t pid_client, char c)
{
	static int	j;

	if (!j)
		j = 0;
	if (c == '\0')
	{
		g_str[j] = '\0';
		j = 0;
		write (1, g_str, ft_strlen(g_str));
		if (kill(pid_client, SIGUSR2) == -1)
		{
			write (1, "Error in Kill_SIGUSR2", 21);
			exit(1);
		}
		return ;
	}
	g_str[j++] = c;
}

void	sig_to_char_handler(int sig, siginfo_t *info, void *context)
{
	static char			c;
	static int			i;
	static __pid_t		pid_client;

	(void)context;
	if (info->si_pid != 0)
		pid_client = info->si_pid;
	if (!i)
		i = 0;
	if (!c)
		c = '\0';
	if (sig == SIGUSR1)
		c |= (1 << i);
	i++;
	if (i == 8)
	{
		i = 0;
		wrt_str(pid_client, c);
		c = 0;
	}
	usleep(100);
	if (kill(pid_client, SIGUSR1) == -1)
	{
		write (1, "Error in Kill_SIGUSR1", 21);
		exit(1);
	}
}

int	main(void)
{
	__pid_t				pid;
	char				*s1;
	struct sigaction	sig_server;

	sig_server.sa_sigaction = sig_to_char_handler;
	sig_server.sa_flags = SA_SIGINFO;
	sigemptyset(&sig_server.sa_mask);
	sigaddset(&sig_server.sa_mask, SIGUSR1);
	sigaddset(&sig_server.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sig_server, NULL);
	sigaction(SIGUSR2, &sig_server, NULL);
	s1 = "I'm the server, my PID is";
	pid = getpid();
	ft_printf ("%s, %d\n", s1, pid);
	while (1)
		pause();
	return (0);
}

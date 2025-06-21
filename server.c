/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:31:17 by cress             #+#    #+#             */
/*   Updated: 2025/06/21 17:25:56 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

char	move_bits(char c, int sig)
{
	static int	i;

	i = 0;
	if (sig == SIGUSR1)
		c += (1 << i);
	else if (sig == SIGUSR2)
		c += (0 << i);
	i++;
	if (i == 8)
	{
		i = 0;
		return (c);
	}
	return (c);
}

void	send_malloc(char c)
{
	static char	*new_str;
	char		new_char[2];
	char		*aux;

	new_char[0] = c;
	new_char[1] = '\0';
	if (new_char[0] == '\0')
	{
		printf("%s", new_str);
		free(new_str);
		new_str = NULL;
	}
	aux = ft_strjoin(new_str, new_char);
	free(new_str);
	new_str = aux;
	free(aux);
}

void	pre_send_malloc(__pid_t pid_client, char c)
{
	if (c == '\0')
	{
		if (kill(pid_client, SIGUSR2) == -1)
		{
			write (1, "Error in Kill_SIGUSR2", 21);
			exit(1);
		}
	}
	send_malloc(c);
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
	c = move_bits(c, sig);
	i++;
	if (i == 8)
	{
		i = 0;
		pre_send_malloc(pid_client, c);
	}
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
	struct sigaction	sig_action;

	sig_action.sa_sigaction = sig_to_char_handler;
	sig_action.sa_flags = SA_SIGINFO;
	sigemptyset(&sig_action.sa_mask);
	sigaddset(&sig_action.sa_mask, SIGUSR1);
	sigaddset(&sig_action.sa_mask, SIGUSR2);

	s1 = "I'm the server, my PID is";
	pid = getpid();
	ft_printf ("%s, %d\n", s1, pid);
	sigaction(SIGUSR1, &sig_action, NULL);
	sigaction(SIGUSR2, &sig_action, NULL);
	while (1)
		pause();
	return (0);
}

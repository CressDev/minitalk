/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:31:17 by cress             #+#    #+#             */
/*   Updated: 2025/06/20 23:51:02 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

char	*send_malloc(char c)
{
	static int	i;
	static char	*new_str;
	static char	*new_char;
	static char	*null_char;

	if (!i)
		i = 0;
	null_char[0] = '\0';
	new_char = (char *)c;
	if (new_char[0] == '\0')
		return (new_str);
	new_str = ft_strjoin(new_char, null_char);
}

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
		return (c);
}

void	sig_to_char_handler(int sig, siginfo_t info)
{
	static char			c;
	static int			i;
	static int			pid_client;

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
		if (c == '\0')
			if (kill(pid_client, SIGUSR2) == -1)
				handler_error(0);
		send_malloc(c);
		i = 0;
		c = 0;
	}
	if (kill(pid_client, SIGUSR1) == -1)
		handler_error(0);
}
int	main(void)
{
	__pid_t	pid;
	char	*s1;

	s1 = "I'm the server, my PID is";
	pid = getpid();
	ft_printf ("%s, %d\n", s1, pid);
	sigaction(SIGUSR1, sig_to_char_handler);
	sigaction(SIGUSR2, sig_to_char_handler);
	while (1)
		pause;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cress <cress@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:31:07 by cress             #+#    #+#             */
/*   Updated: 2025/06/15 11:20:15 by cress            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

void	send_char_to_bin(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i & 1) == 1)
			kill(pid, SIGUSR1);
		if ((c >> i & 1) == 0)
			kill(pid, SIGUSR2);
		usleep(42);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	int		i;

	if (argc == 3)
	{
		i = 0;
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
			send_char_to_bin(pid, argv[2][i++]);
		send_char_to_bin(pid, '\0');
	}
	return (0);
}

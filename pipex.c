/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:03:21 by druina            #+#    #+#             */
/*   Updated: 2023/01/18 09:22:15 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define PROCESS_NUMBER argc - 3

void	error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv /*, char **env*/)
{
	int	pipe_n[PROCESS_NUMBER + 1][2];
	int	i;
	int	pid[PROCESS_NUMBER];

	i = 0;
	ft_printf("pipes number: %d\n", PROCESS_NUMBER - 1);
	while (i < PROCESS_NUMBER + 1)
	{
		if (pipe(pipe_n[i]) == -1)
			error("woah, pipe problem");
		ft_printf("created pipe number: %d\n", i);
		i++;
	}
	i = 0;
	while (i < PROCESS_NUMBER)
	{
		ft_printf("created process number: %d\n", i);
		pid[i] = fork();
		if (pid[i] == -1)
			error("woah, fork problem");
		if (pid[i] == 0)
		{
			ft_printf("entered process: %d\n", i);
			return (child(pipe_n, i, PROCESS_NUMBER));
		}
		i++;
	}
	return (parent(pipe_n, argv, PROCESS_NUMBER));
}

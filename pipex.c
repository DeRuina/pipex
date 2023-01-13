/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:04:34 by druina            #+#    #+#             */
/*   Updated: 2023/01/13 15:59:01 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define PROCESS_NUMBER argc - 4

int	childzero(char **argv, int **pipe_n)
{
	int fd;
	int *str;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error("woah, file opening problem");

	return (EXIT_SUCCESS);
}

void	error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv /*, char **env*/)
{
	int	pipe_n[PROCESS_NUMBER][2];
	int	i;
	int	pid[PROCESS_NUMBER];
	int	j;

	j = 0;
	i = 0;
	while (i < PROCESS_NUMBER)
	{
		if (pipe(pipe_n[i]) == -1)
			error("woah, pipe problem");
		i++;
	}
	i = 0;
	while (i < PROCESS_NUMBER)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			error("woah, fork problem");
		if (pid[i] == 0)
		{
			while (j < PROCESS_NUMBER)
			{
				if (i != j)
				{
					close(pipe_n[j][0]);
					close(pipe_n[j][1]);
				}
				j++;
			}
			if (pid[0])
				return(childzero(argv, pipe_n));
			return (EXIT_SUCCESS);
		}
		i++;
	}
	j = 0;
	while (j < PROCESS_NUMBER)
	{
		if (j != PROCESS_NUMBER - 1)
			close(pipe_n[j][0]);
		close(pipe_n[j][1]);
		j++;
	}
	i = 0;
	while (i++ < PROCESS_NUMBER)
		wait(NULL);
	return (EXIT_SUCCESS);
}

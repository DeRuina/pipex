/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:04:34 by druina            #+#    #+#             */
/*   Updated: 2023/01/13 18:13:24 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define PROCESS_NUMBER argc - 3

void	error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	endchild(int *pipe_n)
{
	int y;
	close(pipe_n[1]);
	if (read(pipe_n[0], &y, sizeof(int)) == -1)
		error("woah, file reading problem - END CHILD");
	close(pipe_n[0]);
	ft_printf("THE TOTAL SUM IS %d\n", y);
	return (EXIT_SUCCESS);
}

int	middlechild(int pipe_n[][2], int i)
{
	int	x;

	if (read(pipe_n[i][0], &x, sizeof(int)) == -1)
		error("woah, file reading problem - MIDDLE CHILD");
	ft_printf("RECIEVED %d\n", x);
	x++;
	if (write(pipe_n[i + 1][1], &x, sizeof(int)) == -1)
		error("woah, file writing problem - MIDDLE CHILD");
	close(pipe_n[i][0]);
	close(pipe_n[i + 1][0]);
	ft_printf("WROTE %d\n", x);
	return (EXIT_SUCCESS);
}

int	childzero(char **argv, int *pipe_n)
{
	int	fd;

	close(pipe_n[0]);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error("woah, file opening problem");
	if (write(pipe_n[1], &fd, sizeof(int)) == -1)
		error("woah, file writing problem - CHILD ZERO");
	ft_printf("ORIGINAL FD IS %d\n", fd);
	close(pipe_n[1]);
	return (EXIT_SUCCESS);
}


int	main(int argc, char **argv /*, char **env*/)
{
	int	pipe_n[PROCESS_NUMBER - 1][2];
	int	i;
	int	pid[PROCESS_NUMBER];
	int	j;

	j = 0;
	i = 0;
	while (i < PROCESS_NUMBER - 1)
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
			while (j < PROCESS_NUMBER - 1)
			{
				if (i != j)
				{
					close(pipe_n[j][0]);
					close(pipe_n[j][1]);
				}
				j++;
			}
			if (pid[0])
				return (childzero(argv, pipe_n[0]));
			else if (pid[PROCESS_NUMBER - 1])
				return (endchild(pipe_n[PROCESS_NUMBER - 2]));
			else
				return (middlechild(pipe_n, i));
		}
		i++;
	}
	j = 0;
	while (j < PROCESS_NUMBER - 1)
	{
		close(pipe_n[j][0]);
		close(pipe_n[j][1]);
		j++;
	}
	i = 0;
	while (i++ < PROCESS_NUMBER)
		wait(NULL);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:04:34 by druina            #+#    #+#             */
/*   Updated: 2023/01/16 16:10:23 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define PROCESS_NUMBER argc - 3

void	error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	endchild(int pipe_n[][2], int i, int processes)
{
	int	y;
	int	j;

	i = 0;
	j = 0;
	while (j < (processes - 1))
	{
		 close(pipe_n[j][1]);
		if (j != processes - 2)
			close(pipe_n[j][0]);
		j++;
	}
	ft_printf("Entered endchild\n");
	if (read(pipe_n[processes - 2][0], &y, sizeof(int)) == -1)
		error("woah, file reading problem - END CHILD");
	close(pipe_n[processes - 2][0]);
	ft_printf("THE TOTAL SUM IS %d\n", y);
	return (EXIT_SUCCESS);
}

int	middlechild(int pipe_n[][2], int i, int processes)
{
	int	x;
	int	j;

	j = 0;
	while (j < processes - 1)
	{
		if (j != i)
			close(pipe_n[j][1]);
		if (j + 1 != i)
			close(pipe_n[j][0]);
		j++;
	}
	ft_printf("Entered middlechild\n");
	if (read(pipe_n[i - 1][0], &x, sizeof(int)) == -1)
		error("woah, file reading problem - MIDDLE CHILD");
	ft_printf("RECIEVED %d\n", x);
	x++;
	if (write(pipe_n[i][1], &x, sizeof(int)) == -1)
		error("woah, file writing problem - MIDDLE CHILD");
	close(pipe_n[i - 1][0]);
	close(pipe_n[i][1]);
	ft_printf("WROTE %d\n", x);
	return (EXIT_SUCCESS);
}

int	childzero(char **argv, int pipe_n[][2], int i, int processes)
{
	int	fd;
	int	x;
	int	j;

	j = 0;
	x = 10;
	while (j < processes - 1)
	{
		close(pipe_n[j][0]);
		if (j != i)
			close(pipe_n[j][1]);
		j++;
	}
	ft_printf("Entered child zero\n");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error("woah, file opening problem");
	ft_printf("read child zero");
	if (write(pipe_n[0][1], &x, sizeof(int)) == -1)
		error("woah, file writing problem - CHILD ZERO");
	ft_printf("ORIGINAL FD IS %d\n", x);
	close(pipe_n[0][1]);
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
	ft_printf("pipes number: %d\n", PROCESS_NUMBER - 1);
	while (i < PROCESS_NUMBER - 1)
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
			if (pid[i] == pid[0])
				return (childzero(argv, pipe_n, i, PROCESS_NUMBER));
			else if (pid[i] == pid[PROCESS_NUMBER - 1])
				return (endchild(pipe_n, i, PROCESS_NUMBER));
			else
				return (middlechild(pipe_n, i, PROCESS_NUMBER));
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
	i = -1;
	while (i++ < PROCESS_NUMBER)
	{
		if (waitpid(pid[i], NULL, 0) == -1)
			error("PROBLEM WITH WAIT IS :");

	}
	return (EXIT_SUCCESS);
}

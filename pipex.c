/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:03:21 by druina            #+#    #+#             */
/*   Updated: 2023/01/17 10:07:51 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define PROCESS_NUMBER argc - 3

void	error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	child(int pipe_n[][2], int i, int processes)
{
	int	x;
	int	j;

	j = 0;
	while (j < processes + 1)
	{
		if (i != j)
			close(pipe_n[j][0]);
		if (i + 1 != j)
			close(pipe_n[j][1]);
		j++;
	}
	ft_printf("Entered middlechild\n");
	if (read(pipe_n[i][0], &x, sizeof(int)) == -1)
		error("woah, file reading problem - MIDDLE CHILD");
	ft_printf("RECIEVED %d\n", x);
	x++;
	if (write(pipe_n[i + 1][1], &x, sizeof(int)) == -1)
		error("woah, file writing problem - MIDDLE CHILD");
	close(pipe_n[i][0]);
	close(pipe_n[i + 1][1]);
	ft_printf("WROTE %d\n", x);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv /*, char **env*/)
{
	int	pipe_n[PROCESS_NUMBER + 1][2];
	int	i;
	int	pid[PROCESS_NUMBER];
	int	fd;
	int	x;

	i = 0;
	x = 10;
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
	i = 0;
	while (i < PROCESS_NUMBER + 1)
	{
		if (i != PROCESS_NUMBER)
			close(pipe_n[i][0]);
		if (i != 0)
			close(pipe_n[i][1]);
		i++;
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error("woah, file opening problem");
	ft_printf("read file\n");
	close(fd);
	if (write(pipe_n[0][1], &x, sizeof(int)) == -1)
		error("woah, file writing problem - CHILD ZERO");
	ft_printf("ORIGINAL X IS %d\n", x);
	close(pipe_n[0][1]);
	if (read(pipe_n[PROCESS_NUMBER][0], &x, sizeof(int)) == -1)
		error("woah, file reading problem - END CHILD");
	close(pipe_n[PROCESS_NUMBER][0]);
	ft_printf("THE TOTAL SUM IS %d\n", x);
	i = 0;
	while (i++ < PROCESS_NUMBER)
	{
		if (waitpid(-1, NULL, 0) == -1)
			error("PROBLEM WITH WAIT IS :");
	}
	return (EXIT_SUCCESS);
}

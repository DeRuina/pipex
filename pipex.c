/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:04:34 by druina            #+#    #+#             */
/*   Updated: 2023/01/16 11:15:16 by druina           ###   ########.fr       */
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
	int	y;

	ft_printf("Entered endchild\n");
	if (read(pipe_n[0], &y, sizeof(int)) == -1)
		error("woah, file reading problem - END CHILD");
	close(pipe_n[0]);
	ft_printf("THE TOTAL SUM IS %d\n", y);
	return (EXIT_SUCCESS);
}

int	middlechild(int pipe_n[][2], int i)
{
	int	x;

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

int	childzero(char **argv, int *pipe_n)
{
	int	fd;
	int	x;

	x = 10;
	ft_printf("Entered child zero\n");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error("woah, file opening problem");
	ft_printf("read child zero");
	if (write(pipe_n[1], &x, sizeof(int)) == -1)
		error("woah, file writing problem - CHILD ZERO");
	ft_printf("ORIGINAL FD IS %d\n", x);
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
		pid[i] = fork();
		ft_printf("created process number: %d\n", i);
		if (pid[i] == -1)
			error("woah, fork problem");
		if (pid[i] == 0)
		{
			ft_printf("entered process: %d\n", i);
			// while (j < PROCESS_NUMBER - 1)
			// {
			// 	if (pid[i] == pid[0])
			// 	{
			// 		close(pipe_n[j][0]);
			// 		if (j != i)
			// 			close(pipe_n[j][1]);

			// 	}
			// 	else if (pid[i] == pid[PROCESS_NUMBER - 1])
			// 	{

			// 		// close(pipe_n[j][1]);
			// 		// if (j + 1 != i)
			// 		// 	close(pipe_n[j][0]);
			// 	}
			// 	//  else
			// 	// {
			// 	// 	ft_printf("this is middle child %d, %d times\n", pid[i], j);
			// 	// // 	if (j != i)
			// 	// // 		close(pipe_n[j][1]);
			// 	// // 	if (j + 1 != i)
			// 	// // 		close(pipe_n[j][0]);
			// 	//  }
			// 	j++;
			// }

			if (pid[i] == pid[0])
				return (childzero(argv, pipe_n[0]));
			else if (pid[i] == pid[PROCESS_NUMBER - 1])
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

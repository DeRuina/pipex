/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:03:21 by druina            #+#    #+#             */
/*   Updated: 2023/01/19 16:16:50 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define PROCESS_NUMBER argc - 3

int	error(char *msg)
{
	perror(msg);
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int	pipe_n[PROCESS_NUMBER][2];
	int	i;
	int	pid[PROCESS_NUMBER - 1];
	int	infile;
	int	j;

	if (argc < 5)
		return (ft_printf("not enough arguments try again\n"));
	i = 0;
	while (i < PROCESS_NUMBER)
	{
		if (pipe(pipe_n[i]) == -1)
			exit(error("woah, pipe problem"));
		i++;
	}
	if ((infile = open(argv[1], O_RDONLY)) == -1)
		perror("woah, file opening problem");
	else
	{
		if (dup2(infile, pipe_n[0][0]) == -1)
			exit(error("woah, dup2 main problem"));
		close(infile);
	}
	i = 0;
	while (i < PROCESS_NUMBER - 1)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			exit(error("woah, fork problem"));
		if (pid[i] == 0)
		{
			j = 0;
			while (j < PROCESS_NUMBER)
			{
				if (i != j)
					close(pipe_n[j][0]);
				if (i + 1 != j)
					close(pipe_n[j][1]);
				j++;
			}
			return (child(pipe_n, i, argv, envp));
		}
		i++;
	}
	return (parent(pipe_n, argv, PROCESS_NUMBER, envp));
}

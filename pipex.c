/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:03:21 by druina            #+#    #+#             */
/*   Updated: 2023/01/19 15:40:36 by druina           ###   ########.fr       */
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
	int j;
	//int outfile;
	i = 0;
	ft_printf("pipes number: %d\n", PROCESS_NUMBER);
	while (i < PROCESS_NUMBER)
	{
		if (pipe(pipe_n[i]) == -1)
			exit(error("woah, pipe problem"));
		ft_printf("created pipe number: %d\n", i);
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
	// // if ((outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC,
	// 				0664)) == -1)
	// // 	return (error("woah, file opening problem"));
	i = 0;
	while (i < PROCESS_NUMBER - 1)
	{
		ft_printf("created process number: %d\n", i);
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
			ft_printf("entered process: %d\n", i);
			return (child(pipe_n, i, argv, envp));
		}
		i++;
	}
	return (parent(pipe_n, argv, PROCESS_NUMBER, envp));
}

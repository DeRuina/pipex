/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:03:21 by druina            #+#    #+#             */
/*   Updated: 2023/01/20 09:57:55 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_child_pipes(int **pipe_n, int i, int proccesses)
{
	int	j;

	j = 0;
	while (j < proccesses)
	{
		if (i != j)
			close(pipe_n[j][0]);
		if (i + 1 != j)
			close(pipe_n[j][1]);
		j++;
	}
}

int	error(char *msg)
{
	perror(msg);
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int	**pipe_n;
	int	i;
	int	*pid;
	int	infile;
	int	proccesses;

	if (argc < 5)
		return (ft_printf("not enough arguments try again\n"));
	pipe_n = allocate_pipes(argc);
	pid = allocate_pid(argc, pipe_n);
	if (pipe_n == NULL || pid == NULL)
		exit(error("allocation fail"));
	proccesses = argc - 3;
	i = 0;
	while (i < proccesses)
	{
		if (pipe(pipe_n[i]) == -1)
			exit(error("woah, pipe problem"));
		i++;
	}
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		perror("woah, file opening problem");
	else
	{
		if (dup2(infile, pipe_n[0][0]) == -1)
			exit(error("woah, dup2 main problem"));
		close(infile);
	}
	i = 0;
	while (i < proccesses - 1)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			exit(error("woah, fork problem"));
		if (pid[i] == 0)
		{
			close_child_pipes(pipe_n, i, proccesses);
			return (child(pipe_n, i, argv, envp));
		}
		i++;
	}
	return (parent(pipe_n, argv, proccesses, envp));
}

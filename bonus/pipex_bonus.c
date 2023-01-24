/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 09:03:21 by druina            #+#    #+#             */
/*   Updated: 2023/01/24 11:24:00 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	error(char *msg)
{
	perror(msg);
	return (EXIT_FAILURE);
}

int	fork_and_check(int *pid, int i)
{
	pid[i] = fork();
	if (pid[i] == -1)
		return (error("woah, fork problem"));
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int	**pipe_n;
	int	i;
	int	*pid;
	int	proccesses;

	if (argc != 5)
		return (ft_printf("wrong amount of arguments try again\n"));
	pipe_n = allocate_pipes(argc, argv);
	pid = allocate_pid(argc, pipe_n, argv);
	if (pipe_n == NULL || pid == NULL)
		exit(error("allocation fail"));
	proccesses = (argc - 3) - is_here_doc(argv);
	create_pipes_and_read_infile(pipe_n, proccesses, argv);
	i = -1;
	while (++i < proccesses - 1)
	{
		if (fork_and_check(pid, i) == -1)
			return (error("woah, fork problem"));
		if (pid[i] == 0)
		{
			close_child_pipes(pipe_n, i, proccesses);
			return (child(pipe_n, i, argv, envp));
		}
	}
	return (parent(pipe_n, argv, proccesses, envp));
}

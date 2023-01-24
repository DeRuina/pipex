/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:28:59 by druina            #+#    #+#             */
/*   Updated: 2023/01/24 11:14:15 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_parent_pipes(int **pipe_n, int proccesses)
{
	int	i;

	i = 0;
	while (i < proccesses)
	{
		close(pipe_n[i][1]);
		if (i != proccesses - 1)
			close(pipe_n[i][0]);
		i++;
	}
}

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

int	open_outfile(char **argv, int proccesses)
{
	int	outfile;

	if (is_here_doc(argv) == 1)
		outfile = open(argv[proccesses + 2 + is_here_doc(argv)],
				O_CREAT | O_WRONLY | O_APPEND, 0664);
	else
		outfile = open(argv[proccesses + 2 + is_here_doc(argv)],
				O_CREAT | O_WRONLY | O_TRUNC, 0664);
	return (outfile);
}

int	parent(int **pipe_n, char **argv, int proccesses, char **envp)
{
	int	i;
	int	outfile;

	close_parent_pipes(pipe_n, proccesses);
	if (dup2(pipe_n[proccesses - 1][0], STDIN_FILENO) == -1)
		return (error("woah, dup2 parent 1 problem"));
	close(pipe_n[proccesses - 1][0]);
	i = 0;
	while (i++ < proccesses - 1)
	{
		if (waitpid(-1, NULL, 0) == -1)
			return (error("PROBLEM WITH WAIT IS"));
	}
	outfile = open_outfile(argv, proccesses);
	if (outfile == -1)
		return (error("woah, file opening problem"));
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return (error("woah, dup2 parent 2 problem"));
	close(outfile);
	get_path_and_cmd(argv[proccesses + 1 + is_here_doc(argv)], envp);
	return (EXIT_SUCCESS);
}

int	child(int **pipe_n, int i, char **argv, char **envp)
{
	if (dup2(pipe_n[i][0], STDIN_FILENO) == -1)
		return (error("woah, dup2 child 1 problem"));
	close(pipe_n[i][0]);
	if (dup2(pipe_n[i + 1][1], STDOUT_FILENO) == -1)
		return (error("woah, dup2 child 2 problem"));
	close(pipe_n[i + 1][1]);
	get_path_and_cmd(argv[i + 2 + is_here_doc(argv)], envp);
	return (EXIT_SUCCESS);
}

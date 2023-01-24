/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_pid_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:48:17 by druina            #+#    #+#             */
/*   Updated: 2023/01/24 11:14:21 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	**allocate_pipes(int argc, char **argv)
{
	int	**pipe_n;
	int	i;
	int	len;

	len = (argc - 3) - is_here_doc(argv);
	i = 0;
	pipe_n = ft_calloc(len, sizeof(int *));
	if (!pipe_n)
		return (NULL);
	while (i < len)
	{
		pipe_n[i] = ft_calloc(2, sizeof(int));
		if (!pipe_n[i])
		{
			free(pipe_n);
			return (NULL);
		}
		i++;
	}
	return (pipe_n);
}

int	*allocate_pid(int argc, int **pipe_n, char **argv)
{
	int	*pid;
	int	len;

	len = (argc - 4) - is_here_doc(argv);
	pid = ft_calloc(len, sizeof(int));
	if (!pid)
	{
		free(pipe_n);
		return (NULL);
	}
	return (pid);
}

void	create_pipes_and_read_infile(int **pipe_n, int proccesses, char **argv)
{
	int	i;
	int	infile;

	i = 0;
	while (i < proccesses)
	{
		if (pipe(pipe_n[i]) == -1)
			exit(error("woah, pipe problem"));
		i++;
	}
	if (is_here_doc(argv) == 1)
		infile = here_doc(argv);
	else
		infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		perror("woah, file opening problem");
	else
	{
		if (dup2(infile, pipe_n[0][0]) == -1)
			exit(error("woah, dup2 main problem"));
		close(infile);
	}
}

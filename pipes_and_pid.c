/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_pipe_and_pid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:48:17 by druina            #+#    #+#             */
/*   Updated: 2023/01/20 11:02:18 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**allocate_pipes(int argc)
{
	int	**pipe_n;
	int	i;
	int	len;

	len = argc - 3;
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

int	*allocate_pid(int argc, int **pipe_n)
{
	int	*pid;

	pid = ft_calloc((argc - 4), sizeof(int));
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

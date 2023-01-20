/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_pipe_and_pid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:48:17 by druina            #+#    #+#             */
/*   Updated: 2023/01/20 09:48:53 by druina           ###   ########.fr       */
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

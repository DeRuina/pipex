/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:28:59 by druina            #+#    #+#             */
/*   Updated: 2023/01/19 08:26:35 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parent(int pipe_n[][2], char **argv, int proccesses)
{
	int	i;
	int	fd;
	int	x;

	x = 10;
	i = 0;
	while (i < proccesses + 1)
	{
		if (i != proccesses)
			close(pipe_n[i][0]);
		if (i != 0)
			close(pipe_n[i][1]);
		i++;
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (error("woah, file opening problem"));
	ft_printf("read file\n");
	close(fd);
	if (write(pipe_n[0][1], &x, sizeof(int)) == -1)
		return (error("woah, file writing problem - CHILD ZERO"));
	ft_printf("ORIGINAL X IS %d\n", x);
	close(pipe_n[0][1]);
	if (read(pipe_n[proccesses][0], &x, sizeof(int)) == -1)
		return (error("woah, file reading problem - END CHILD"));
	close(pipe_n[proccesses][0]);
	ft_printf("THE TOTAL SUM IS %d\n", x);
	i = 0;
	while (i++ < proccesses)
	{
		if (waitpid(-1, NULL, 0) == -1)
			return (error("PROBLEM WITH WAIT IS :"));
	}
	return (EXIT_SUCCESS);
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
		return (error("woah, file reading problem - MIDDLE CHILD"));
	ft_printf("RECIEVED %d\n", x);
	x++;
	if (write(pipe_n[i + 1][1], &x, sizeof(int)) == -1)
		return (error("woah, file writing problem - MIDDLE CHILD"));
	close(pipe_n[i][0]);
	close(pipe_n[i + 1][1]);
	ft_printf("WROTE %d\n", x);
	return (EXIT_SUCCESS);
}

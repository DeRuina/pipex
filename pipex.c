/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:04:34 by druina            #+#    #+#             */
/*   Updated: 2023/01/13 11:13:21 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define PROCESS_NUMBER argc - 4

void error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv /*, char **env*/)
{
	int	pipe_n[PROCESS_NUMBER][2];
	int fd;
	int i;
	int pid[PROCESS_NUMBER];
	int j;

	j = 0;
	i = 0;
	while (i < PROCESS_NUMBER)
	{
		if (pipe(pipe_n[i]) == -1)
			error("woah, I have a problem");
		i++;
	}
	i = 0;
	while(i < PROCESS_NUMBER)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			while(j < PROCESS_NUMBER)
			{
				if(i != j)
				{
					close(pipe_n[j][0]);
					close(pipe_n[j][1]);
				}
				j++;
			}


			return(EXIT_SUCCESS);
		}
		i++;
	}
	i = 0;
	while(i++ < PROCESS_NUMBER)
		wait(NULL);

	if ((fd = open(argv[1], O_RDONLY)) == -1)
		perror("woah, I have a problem");

	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:04:34 by druina            #+#    #+#             */
/*   Updated: 2023/01/12 16:29:04 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#define PROCESS_NUMBER argc - 3

int	main(int argc, char **argv /*, char **envp*/)
{
	int	pipe[PROCESS_NUMBER][2];
	int fd;


	if ((fd = open(argv[1], O_RDONLY)) == -1)
		perror("woah, I have a problem");

	return (0);
}

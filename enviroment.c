/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:33:00 by druina            #+#    #+#             */
/*   Updated: 2023/01/17 13:42:20 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*getpath(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
			return (*envp + 5);
		else
			envp++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char *path;
	char **paths;
	argc = 0;
	argv = 0;
	path =  getpath(envp);
	ft_printf("%s\n", path);
	paths = ft_split(path, ':');
	while(*paths)
	{
		printf("%s\n", *paths);
		paths++;
	}
	return (0);
}

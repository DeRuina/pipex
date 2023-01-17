/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:33:00 by druina            #+#    #+#             */
/*   Updated: 2023/01/17 15:44:38 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_from_env(char **envp)
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

char *get_path_and_cmd(char **argv, char **envp)
{
	int i;
	char *path;
	char **possible_paths;
	char **my_execve_args;
	char *cmd;
	char **temp;

	i = 0;
	path =  get_path_from_env(envp);
	possible_paths = ft_split(path, ':');
	temp = possible_paths;
	while (*argv)
	{
		my_execve_args = ft_split(*argv, ' ');
		while(*possible_paths)
		{
			cmd = ft_strjoin(*possible_paths, "/");
			cmd = ft_strjoin(cmd, my_execve_args[0]);
			ft_printf("%s\n", cmd);
			if (access(cmd, X_OK | F_OK) == 0)
				ft_printf(" YES I FOUND IT in %s\n", cmd);
			else
				free(cmd);
			possible_paths++;
		}
		possible_paths = temp;
		argv++;
	}
	return (cmd);
}


int	main(int argc, char **argv, char **envp)
{
	char *path;
	char **paths;
	argc = 0;
	path =  get_path_from_env(envp);
	ft_printf("%s\n", path);
	paths = ft_split(path, ':');
	while(*paths)
	{
		printf("%s\n", *paths);
		paths++;
	}
	ft_printf("%s\n", get_path_and_cmd(argv, envp));
	return (0);
}

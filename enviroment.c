/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:33:00 by druina            #+#    #+#             */
/*   Updated: 2023/01/18 11:01:20 by druina           ###   ########.fr       */
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

char	**possible_paths(char **envp)
{
	char	*path;
	char	**possible_paths;
	char	**temp;

	path = get_path_from_env(envp);
	possible_paths = ft_split(path, ':');
	if (!possible_paths)
		return (NULL);
	temp = possible_paths;
	while (*possible_paths)
	{
		*possible_paths = ft_strjoin(*possible_paths, "/");
		if (!*possible_paths)
		{
			free(possible_paths);
			return (NULL);
		}
		possible_paths++;
	}
	return (temp);
}

char	*get_path_and_cmd(char **argv, char **envp)
{
	char	**paths;
	char	**my_execve_args;
	char	*cmd;
	char	**temp;

	paths = possible_paths(envp);
	temp = paths;
	while (*argv)
	{
		my_execve_args = ft_split(*argv, ' ');
		while (*paths)
		{
			cmd = ft_strjoin(*paths, my_execve_args[0]);
			if (!cmd)
				return (NULL);
			ft_printf("%s\n", cmd);
			if (access(cmd, X_OK | F_OK) == 0)
			{
				if (execve(cmd, my_execve_args, envp) == -1)
					perror("execve problem");
			}
			else
				free(cmd);
			paths++;
		}
		paths = temp;
		argv++;
	}
	return (cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	char	**paths;

	argc = 0;
	path = get_path_from_env(envp);
	ft_printf("%s\n", path);
	paths = possible_paths(envp);
	while (*paths)
	{
		printf("%s\n", *paths);
		paths++;
	}
	get_path_and_cmd(argv, envp);
	return (0);
}

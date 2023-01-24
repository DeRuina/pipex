/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:33:00 by druina            #+#    #+#             */
/*   Updated: 2023/01/24 11:14:31 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

	path = get_path_from_env(envp);
	possible_paths = ft_split(path, ':');
	if (!possible_paths)
		return (NULL);
	return (possible_paths);
}

void	free_2d(char **str)
{
	char	**temp;

	temp = str;
	while (*str)
	{
		free(*str);
		str++;
	}
	free(temp);
}

char	*join_and_free(char *path, char *arg)
{
	char	*addslash;
	char	*cmd;

	addslash = ft_strjoin(path, "/");
	free(path);
	cmd = ft_strjoin(addslash, arg);
	free(addslash);
	if (!cmd)
		return (NULL);
	return (cmd);
}

char	*get_path_and_cmd(char *argv, char **envp)
{
	char	**paths;
	char	**my_execve_args;
	char	*cmd;
	char	**temp;

	paths = possible_paths(envp);
	temp = paths;
	my_execve_args = ft_split(argv, ' ');
	while (*paths)
	{
		if (access(my_execve_args[0], X_OK | F_OK) == 0)
			cmd = my_execve_args[0];
		else
			cmd = join_and_free(*paths, my_execve_args[0]);
		if (access(cmd, X_OK | F_OK) == 0)
			break ;
		else
			free(cmd);
		paths++;
	}
	free(temp);
	if (execve(cmd, my_execve_args, envp) == -1)
		perror("execve problem");
	free_2d(my_execve_args);
	return (cmd);
}

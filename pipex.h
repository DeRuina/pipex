/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:04:41 by druina            #+#    #+#             */
/*   Updated: 2023/01/19 13:40:36 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int		error(char *msg);
int		child(int pipe_n[][2], int i, char **argv, char **envp);
int		parent(int pipe_n[][2], char **argv, int proccesses, char **envp);
char	*get_path_from_env(char **envp);
char	**possible_paths(char **envp);
char	*get_path_and_cmd(char *argv, char **envp);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:04:41 by druina            #+#    #+#             */
/*   Updated: 2023/01/20 11:01:37 by druina           ###   ########.fr       */
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
int		child(int **pipe_n, int i, char **argv, char **envp);
int		parent(int **pipe_n, char **argv, int proccesses, char **envp);
char	*get_path_from_env(char **envp);
char	**possible_paths(char **envp);
char	*get_path_and_cmd(char *argv, char **envp);
void	close_parent_pipes(int **pipe_n, int proccesses);
void	close_child_pipes(int **pipe_n, int i, int proccesses);
int		*allocate_pid(int argc, int **pipe_n);
int		**allocate_pipes(int argc);
void	create_pipes_and_read_infile(int **pipe_n, int proccesses, char **argv);
int		fork_and_check(int *pid, int i);

#endif

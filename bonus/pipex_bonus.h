/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:04:41 by druina            #+#    #+#             */
/*   Updated: 2023/01/25 11:14:47 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int		error(char *msg);
void	free_2d(char **str);
int		child(int **pipe_n, int i, char **argv, char **envp);
int		parent(int **pipe_n, char **argv, int proccesses, char **envp);
char	*get_path_from_env(char **envp);
char	**possible_paths(char **envp);
char	*get_path_and_cmd(char *argv, char **envp);
void	close_parent_pipes(int **pipe_n, int proccesses);
void	close_child_pipes(int **pipe_n, int i, int proccesses);
int		*allocate_pid(int argc, int **pipe_n, char **argv);
int		**allocate_pipes(int argc, char **argv);
void	create_pipes_and_read_infile(int **pipe_n, int proccesses, char **argv);
int		fork_and_check(int *pid, int i);
int		is_here_doc(char **argv);
int		here_doc(char **argv);
void	reopen_file_and_check(int infile);
int		open_outfile(char **argv, int proccesses);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 08:59:34 by druina            #+#    #+#             */
/*   Updated: 2023/01/24 11:14:26 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	is_here_doc(char **argv)
{
	int	check;

	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		check = 1;
	else
		check = 0;
	return (check);
}

void	reopen_file_and_check(int infile)
{
	infile = open("here_doc", O_RDONLY);
	if (infile == -1)
	{
		unlink("here_doc");
		perror("woah, here _doc file opening problem");
	}
}

int	here_doc(char **argv)
{
	int		infile;
	char	*line;

	infile = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (infile == -1)
		perror("woah, here _doc file opening problem");
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
		if (line == NULL)
			return (-1);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
			break ;
		write(infile, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(infile);
	reopen_file_and_check(infile);
	return (infile);
}

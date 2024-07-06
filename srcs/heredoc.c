/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:58:10 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/06 15:58:11 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_line(char **argv, int *fd)
{
	char	*output;

	ft_putstr_fd("pipe heredoc: ", 1);
	output = get_next_line(0);
	while (output)
	{
		if (ft_strncmp(output, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(output);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], output, ft_strlen(output));
		ft_putstr_fd("pipe heredoc: ", 1);
		free(output);
		output = get_next_line(0);
	}
	return (output);
}

int	handle_here_doc(char **argv)
{
	int		fd[2];
	char	*output;
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		close(fd[0]);
		output = get_line(argv, fd);
		free(output);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
	close(fd[0]);
	return (EXIT_SUCCESS);
}

int	handle_heredoc_pipes(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	pipex;

	i = 2;
	init_pipex(&pipex, argc);
	parse_argument(&pipex, argc, argv, envp);
	while (i < argc - 2)
	{
		child_process(&pipex, i - 2, envp);
		i++;
	}
	init_fd(&pipex, argc, argv, 3);
	duplicate(&pipex, 2);
	last_child_process(&pipex, i - 2, envp);
	while (waitpid(-1, NULL, 0) > 0)
	{
	}
	exec_error(&pipex, argv, argc);
	ft_free_and_close(&pipex);
	return (EXIT_SUCCESS);
}

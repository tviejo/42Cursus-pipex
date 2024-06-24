/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:20:38 by tviejo            #+#    #+#             */
/*   Updated: 2024/06/24 10:20:40 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	wait_for_child(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
	{
		printf("waitpid failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	create_pipe(t_pipex *pipex)
{
	if (pipe(pipex->fdpipe) == -1)
	{
		printf("pipe failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	close_pipe(t_pipex *pipex)
{
	if (pipex->fdpipe[0] != -1)
		close(pipex->fdpipe[0]);
	if (pipex->fdpipe[1] != -1)
		close(pipex->fdpipe[1]);
	return (EXIT_SUCCESS);
}

int	duplicate_pipe(t_pipex *pipex, int mode)
{
	if (mode == 1)
	{
		if (dup2(pipex->fdpipe[1], STDOUT_FILENO) == -1)
			ft_close_error(pipex);
		close(pipex->fdpipe[1]);
		pipex->fdpipe[1] = -1;
	}
	else
	{
		if (dup2(pipex->fdpipe[0], STDIN_FILENO) == -1)
			ft_close_error(pipex);
		close(pipex->fdpipe[0]);
		pipex->fdpipe[0] = -1;
	}
	return (EXIT_SUCCESS);
}

void	close_fd(int fd, t_pipex *pipex)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
		{
			ft_close_error(pipex);
		}
	}
}

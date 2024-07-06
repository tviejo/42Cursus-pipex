/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:20:38 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/06 13:27:56 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	*ft_calloc_pid(t_pipex *pipex, int argc)
{
	pipex->pid = ft_calloc(argc, sizeof(pid_t));
	if (pipex->pid == NULL)
		ft_close_error(pipex, 2);
	ft_memset(pipex->pid, -10, argc);
	return (pipex->pid);
}

int	create_pipe(t_pipex *pipex)
{
	if (pipe(pipex->fdpipe) == -1)
	{
		ft_close_error(pipex, 2);
	}
	return (EXIT_SUCCESS);
}

int	close_pipe(t_pipex *pipex)
{
	if (pipex->fdpipe[0] > 2)
		close(pipex->fdpipe[0]);
	if (pipex->fdpipe[1] > 2)
		close(pipex->fdpipe[1]);
	return (EXIT_SUCCESS);
}

int	duplicate_pipe(t_pipex *pipex, int mode)
{
	if (mode == 1)
	{
		if (dup2(pipex->fdpipe[1], STDOUT_FILENO) == -1)
			ft_close_error(pipex, 2);
		close(pipex->fdpipe[1]);
		pipex->fdpipe[1] = -1;
	}
	else
	{
		if (dup2(pipex->fdpipe[0], STDIN_FILENO) == -1)
			ft_close_error(pipex, 2);
		close(pipex->fdpipe[0]);
		pipex->fdpipe[0] = -1;
	}
	return (EXIT_SUCCESS);
}

int	close_fd(int fd, t_pipex *pipex)
{
	if (fd >= 0 && fd <= 1024)
	{
		if (close(fd) == -1)
		{
			ft_close_error(pipex, 2);
		}
	}
	return (-1);
}

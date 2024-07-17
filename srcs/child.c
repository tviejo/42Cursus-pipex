/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:51:21 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/17 10:36:32 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	child_process(t_pipex *pipex, int index, char **envp)
{
	create_pipe(pipex);
	pipex->pid[index] = fork();
	if (pipex->pid[index] == -1)
		ft_close_error(pipex, 2);
	else if (pipex->pid[index] == 0)
	{
		pipex->fdpipe[0] = close_fd(pipex->fdpipe[0], pipex);
		duplicate_pipe(pipex, 1);
		exec_cmd(pipex, index, envp);
	}
	else
	{
		pipex->fdpipe[1] = close_fd(pipex->fdpipe[1], pipex);
		duplicate_pipe(pipex, 2);
		pipex->fdpipe[0] = close_fd(pipex->fdpipe[0], pipex);
	}
	close_pipe(pipex);
	return (EXIT_SUCCESS);
}

int	last_child_process(t_pipex *pipex, int index, char **envp)
{
	pipex->pid[index] = fork();
	if (pipex->pid[index] == -1)
		ft_close_error(pipex, 2);
	else if (pipex->pid[index] == 0)
	{
		exec_cmd(pipex, index, envp);
	}
	return (EXIT_SUCCESS);
}

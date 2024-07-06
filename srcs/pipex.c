/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:20:31 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/06 15:42:30 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	init_fd(t_pipex *pipex, int argc, char **argv, int mode)
{
	if (mode == 1)
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
		{
			ft_close_error(pipex, 2);
		}
	}
	else if (mode == 2)
	{
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (pipex->outfile < 0)
		{
			ft_close_error(pipex, 2);
		}
	}
	else if (mode == 3)
	{
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
	}
	return (EXIT_SUCCESS);
}

void	init_pipex(t_pipex *pipex, int argc)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->fdpipe[0] = -1;
	pipex->fdpipe[1] = -1;
	pipex->path = NULL;
	pipex->arguments = NULL;
	pipex->pid = ft_calloc_pid(pipex, argc);
}

int	duplicate(t_pipex *pipex, int mode)
{
	if (mode == 1)
	{
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			ft_close_error(pipex, 2);
		pipex->infile = close_fd(pipex->infile, pipex);
	}
	else if (mode == 2)
	{
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			ft_close_error(pipex, 2);
		pipex->outfile = close_fd(pipex->outfile, pipex);
	}
	return (EXIT_SUCCESS);
}

int	handle_multiple_pipes(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	pipex;

	i = 2;
	init_pipex(&pipex, argc);
	init_fd(&pipex, argc, argv, 1);
	parse_argument(&pipex, argc, argv, envp);
	duplicate(&pipex, 1);
	while (i < argc - 2)
	{
		child_process(&pipex, i - 2, envp);
		i++;
	}
	init_fd(&pipex, argc, argv, 2);
	duplicate(&pipex, 2);
	last_child_process(&pipex, i - 2, envp);
	while (waitpid(-1, NULL, 0) > 0)
	{
	}
	exec_error(&pipex, argv, argc);
	ft_free_and_close(&pipex);
	return (EXIT_SUCCESS);
}

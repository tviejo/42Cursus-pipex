/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:20:17 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/06 13:44:49 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_error(t_pipex *pipex, char **argv, int argc)
{
	int	index;
	int	fd;

	index = 0;
	while (pipex->arguments[index] != NULL)
	{
		if (pipex->arguments[index][0] == NULL)
		{
			fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(fd);
		}
		index++;
	}
}

void	exec_cmd(t_pipex *pipex, int index, char **envp)
{
	char	**commands;
	int		output;

	output = 0;
	commands = pipex->arguments[index];
	if (commands == NULL)
		ft_close_error(pipex, 2);
	if (commands[0] != NULL)
	{
		execve(commands[0], commands, envp);
		perror("Error");
	}
}

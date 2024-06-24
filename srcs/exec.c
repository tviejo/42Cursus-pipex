/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:20:17 by tviejo            #+#    #+#             */
/*   Updated: 2024/06/24 10:20:18 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	exec_cmd(t_pipex *pipex, int index, char **envp)
{
	char	**commands;

	commands = pipex->arguments[index];
	if (commands == NULL)
		ft_close_error(pipex);
	if (execve(commands[0], commands, envp) < 0)
		ft_close_error(pipex);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:20:08 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/06 13:44:15 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_arguments(char ***arguments)
{
	int	i;
	int	j;

	i = 0;
	while (arguments[i] != NULL)
	{
		j = 0;
		while (arguments[i][j] != NULL)
		{
			free(arguments[i][j]);
			j++;
		}
		free(arguments[i]);
		i++;
	}
	free(arguments);
}

void	ft_free_and_close(t_pipex *pipex)
{
	if (pipex->infile > 2)
		close(pipex->infile);
	if (pipex->outfile > 2)
		close(pipex->outfile);
	if (pipex->fdpipe[0] > 2)
		close(pipex->infile);
	if (pipex->fdpipe[1] > 2)
		close(pipex->outfile);
	if (pipex->arguments != NULL)
		ft_free_arguments(pipex->arguments);
	free(pipex->pid);
}

void	ft_close_error(t_pipex *pipex, int mode)
{
	perror("Error");
	if (mode == 1)
	{
		if (pipex->path != NULL)
			ft_free_split(pipex->path);
	}
	ft_free_and_close(pipex);
	exit(EXIT_FAILURE);
}

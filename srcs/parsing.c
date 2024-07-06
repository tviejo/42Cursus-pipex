/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:20:24 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/06 15:38:48 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp(*envp, "PATH=", 5) != 0 && *envp != NULL)
		envp++;
	if (ft_strncmp(*envp, "PATH=", 5) == 0)
		return (*envp + 5);
	else
	{
		ft_close_error(NULL, 2);
		return (NULL);
	}
}

char	*find_cmd(char *cmd, char **paths)
{
	char	*tmp;
	char	*tmppath;
	int		i;

	i = 0;
	tmp = NULL;
	tmppath = NULL;
	while (paths[i] != NULL)
	{
		free(tmp);
		free(tmppath);
		tmppath = ft_strjoin(paths[i], "/");
		if (tmppath == NULL)
			break ;
		tmp = ft_strjoin(tmppath, cmd);
		if (tmp != NULL && access(tmp, F_OK | X_OK) == 0)
		{
			free(tmppath);
			return (tmp);
		}
		i++;
	}
	ft_printf("command not found: %s\n", cmd);
	return (free(tmppath), free(tmp), NULL);
}

void	parse_argument(t_pipex *pipex, int argc, char **arg, char **envp)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	path = find_path(envp);
	pipex->path = ft_split(path, ':');
	pipex->arguments = (char ***)ft_calloc(sizeof(char **), argc - 2);
	if (pipex->path == NULL || pipex->arguments == NULL)
		ft_close_error(pipex, 1);
	while (i < argc - 3)
	{
		pipex->arguments[i] = ft_split(arg[i + 2], ' ');
		if (pipex->arguments[i] == NULL)
			ft_close_error(pipex, 1);
		tmp = find_cmd(pipex->arguments[i][0], pipex->path);
		free(pipex->arguments[i][0]);
		pipex->arguments[i][0] = tmp;
		i++;
	}
	ft_free_split(pipex->path);
	pipex->arguments[i] = NULL;
}

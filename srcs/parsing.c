#include "../includes/pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	return (*envp + 5);
}

char	*find_cmd(t_pipex *pipex, char *cmd, char **paths)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (paths[i] != NULL)
	{
		free(tmp);
		tmp = ft_strjoin(paths[i], "/");
		if (tmp == NULL)
		{
			free(tmp);
			ft_close_error(pipex);
		}
		tmp = ft_strjoin(tmp, cmd);
		if (tmp != NULL && access(tmp, F_OK) == 0)
			return (tmp);
		i++;
	}
	free(tmp);
	return (NULL);
}

void	parse_argument(t_pipex *pipex, int argc, char **arg, char **envp)
{
	char	*path;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	path = find_path(envp);
	pipex->path = ft_split(path, ':');
	pipex->arguments = (char ***)ft_calloc(sizeof(char **) ,argc);
	while (i < argc - 3)
	{
		pipex->arguments[i + 1] = NULL;
		pipex->arguments[i] = ft_split(arg[i + 2], ' ');
		if (pipex->arguments[i] == NULL)
			ft_close_error(pipex);
		tmp = find_cmd(pipex, pipex->arguments[i][0], pipex->path);
		if (tmp == NULL)
		{
			free(tmp);
			ft_close_error(pipex);
		}
		free(pipex->arguments[i][0]);
		pipex->arguments[i][0] = tmp;
		i++;
		j++;
	}
	free(pipex->path);
	pipex->arguments[i] = NULL;
}

#include "../includes/pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	return (*envp + 5);
}

char	*find_cmd(char *cmd, char **paths)
{
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		i++;
	}
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
	pipex->arguments = (char ***)malloc(sizeof(char **) * argc);
	while (i < argc - 2)
	{
		pipex->arguments[i] = ft_split(arg[i + 2], ' ');
		if (pipex->arguments[i] == NULL)
			ft_close_error(pipex);
		tmp = find_cmd(pipex->arguments[i][0], pipex->path);
		free(pipex->arguments[i][0]);
		pipex->arguments[i][0] = tmp;
		i++;
		j++;
	}
	free(pipex->path);
	pipex->arguments[i] = NULL;
}

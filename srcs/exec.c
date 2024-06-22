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
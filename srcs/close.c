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
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->arguments != NULL)
		ft_free_arguments(pipex->arguments);
	if (pipex->path != NULL)
		ft_free_split(pipex->path);
}

void	ft_close_error(t_pipex *pipex)
{
	if (errno != 0)
		ft_printf("fail: %s\n", strerror(errno));
	ft_free_and_close(pipex);
	exit(EXIT_FAILURE);
}
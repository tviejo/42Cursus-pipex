#include "../includes/pipex.h"

int	wait_for_child(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
	{
		printf("waitpid failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	create_pipe(t_pipex *pipex)
{
	if (pipe(pipex->fdpipe) == -1)
	{
		printf("pipe failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	close_pipe(t_pipex *pipex)
{
	if (pipex->fdpipe[0] != -1)
		close(pipex->fdpipe[0]);
	if (pipex->fdpipe[1] != -1)
		close(pipex->fdpipe[1]);
	return (EXIT_SUCCESS);
}
int	duplicate_pipe(t_pipex *pipex, int mode)
{
	if (mode == 1)
	{
		if (dup2(pipex->fdpipe[1], STDOUT_FILENO) == -1)
			ft_close_error(pipex);
		close(pipex->fdpipe[1]);
		pipex->fdpipe[1] = -1;
	}
	else
	{
		if (dup2(pipex->fdpipe[0], STDIN_FILENO) == -1)
			ft_close_error(pipex);
		close(pipex->fdpipe[0]);
		pipex->fdpipe[0] = -1;
	}
	return (EXIT_SUCCESS);
}

void	close_fd(int fd, t_pipex *pipex)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
		{
			ft_close_error(pipex);
		}
	}
}

int	child_process(t_pipex *pipex, int index, char **envp)
{
	pid_t	pid;

	create_pipe(pipex);
	pid = fork();
	if (pid == -1)
		ft_close_error(pipex);
	else if (pid == 0)
	{
		close_fd(pipex->fdpipe[0], pipex);
		duplicate_pipe(pipex, 1);
		exec_cmd(pipex, index, envp);
	}
	else
	{
		close_fd(pipex->fdpipe[1], pipex);
		duplicate_pipe(pipex, 2);
		close_fd(pipex->fdpipe[0], pipex);
		pipex->fdpipe[0] = -1;
		wait_for_child(pid);
	}
	close_pipe(pipex);
	return (EXIT_SUCCESS);
}

int	init_fd(t_pipex *pipex, int argc, char **argv, int mode)
{
	if (mode == 1)
	{
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
		{
			printf("open failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		pipex->outfile = -1;
	}
	else
	{
		pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0777);
		if (pipex->outfile < 0)
		{
			printf("open failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		pipex->infile = -1;
	}
	return (EXIT_SUCCESS);
}

void	init_pipex(t_pipex *pipex)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->fdpipe[0] = -1;
	pipex->fdpipe[1] = -1;
	pipex->path = NULL;
	pipex->arguments = NULL;
}
int	duplicate(t_pipex *pipex, int mode)
{
	if (mode == 1)
	{
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			ft_close_error(pipex);
		close_fd(pipex->infile, pipex);
	}
	else
	{
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			ft_close_error(pipex);
		close_fd(pipex->outfile, pipex);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	pipex;

	if (argc < 5)
	{
		printf("use this format: ./pipex file1 cmd1 cmd2 file2\n");
		exit(EXIT_FAILURE);
	}
	init_pipex(&pipex);
	init_fd(&pipex, argc, argv, 1);
	parse_argument(&pipex, argc, argv, envp);
	duplicate(&pipex, 1);
	i = 2;
	while (i < argc - 2)
	{
		child_process(&pipex, i - 2, envp);
		i++;
	}
	init_fd(&pipex, argc, argv, 2);
	duplicate(&pipex, 2);
	exec_cmd(&pipex, i - 2, envp);
	ft_free_and_close(&pipex);
	return (EXIT_SUCCESS);
}

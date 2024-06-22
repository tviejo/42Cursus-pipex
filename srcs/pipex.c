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

int	child_process(t_pipex *pipex, int index, char **envp)
{
	pid_t	pid;
	int		fd[2];
	int		err;

	err = pipe(fd);
	pid = fork();
	if (pid == -1 || err == -1)
		ft_close_error(pipex);
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close (fd[1]);
		exec_cmd(pipex, index, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait_for_child(pid);
	}
	return (EXIT_SUCCESS);
}
int	init_fd(t_pipex *pipex, int argc, char **argv)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		printf("open failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->outfile < 0)
	{
		printf("open failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void init_pipex(t_pipex *pipex)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->path = NULL;
	pipex->arguments = NULL;
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
	init_fd(&pipex, argc, argv);
	parse_argument(&pipex, argc, argv, envp);
	if (dup2(pipex.infile, STDIN_FILENO) == -1)
		ft_close_error(&pipex);
	close(pipex.infile);
	pipex.infile = -1;
	i = 2;
	while (i < argc - 2)
	{
		child_process(&pipex, i - 2, envp);
		i++;
	}
	if (dup2(pipex.outfile, STDOUT_FILENO) == -1)
		ft_close_error(&pipex);
	close(pipex.outfile);
	pipex.outfile = -1;
	exec_cmd(&pipex, i - 2, envp);
	ft_free_and_close(&pipex);
	return (EXIT_SUCCESS);
}

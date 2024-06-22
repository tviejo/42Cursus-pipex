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
		close(fd[1]);
		exec_cmd(pipex, index, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait_for_child(pid);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	pipex;

	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	parse_argument(&pipex, argc, argv, envp);
	dup2(pipex.infile, STDIN_FILENO);
	close(pipex.infile);
	pipex.infile = -1;
	i = 2;
	while (i < argc - 2)
	{
		child_process(&pipex, i - 2, envp);
		i++;
	}
	dup2(pipex.outfile, STDOUT_FILENO);
	close(pipex.outfile);
	pipex.outfile = -1;
	exec_cmd(&pipex, i - 2, envp);
	ft_free_and_close(&pipex);
	return (EXIT_SUCCESS);
}

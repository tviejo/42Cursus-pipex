#include "../includes/pipex.h"

int handle_here_doc(int argc, char **argv, char **envp)
{
    ft_putendl_fd("pipe heredoc", 1);
    while (strncmp(get_next_line(0), argv[2], ft_strlen(argv[2])) != 0)
    {
        ft_putendl_fd("pipe heredoc", 1);
    }
    argc++;
    envp[0] = NULL;
    return (EXIT_SUCCESS);
}
int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		printf("use this format: ./pipex file1 cmd1 cmd2 file2\n");
		ft_close_error(NULL);
	}
    else if (strncmp(argv[1], "here_doc", 8) == 0 && argc == 6)
    {
        handle_here_doc(argc, argv, envp);
    }
	else if (strncmp(argv[1], "here_doc", 8) != 0)
    {
        handle_multiple_pipes(argc, argv, envp);
    }
    else
	{
		printf("use this format: ./pipex file1 cmd1 cmd2 file2\n");
		ft_close_error(NULL);
	}
	return (EXIT_SUCCESS);
}

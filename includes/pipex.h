#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		outfile;
	int		infile;
	char	***arguments;
	char	**path;
	int		fdpipe[2];
}			t_pipex;

int			exec_cmd(t_pipex *pipex, int index, char **envp);
void		parse_argument(t_pipex *pipex, int argc, char **arg, char **envp);
void		ft_close_error(t_pipex *pipex);
void		ft_free_and_close(t_pipex *pipex);

#endif
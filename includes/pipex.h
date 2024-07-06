/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:21:00 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/06 15:05:16 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
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
	int		nb_arguments;
	char	**path;
	int		fdpipe[2];
	pid_t	*pid;
}			t_pipex;

void		*ft_calloc_pid(t_pipex *pipex, int argc);
void		exec_cmd(t_pipex *pipex, int index, char **envp);
void		parse_argument(t_pipex *pipex, int argc, char **arg, char **envp);
void		ft_close_error(t_pipex *pipex, int mode);
void		ft_free_and_close(t_pipex *pipex);
int			handle_multiple_pipes(int argc, char **argv, char **envp);
int			close_fd(int fd, t_pipex *pipex);
int			duplicate_pipe(t_pipex *pipex, int mode);
int			close_pipe(t_pipex *pipex);
int			create_pipe(t_pipex *pipex);
int			wait_for_child(pid_t pid, t_pipex *pipex);
void		exec_error(t_pipex *pipex, char **argv, int argc);
int			last_child_process(t_pipex *pipex, int index, char **envp);
int			child_process(t_pipex *pipex, int index, char **envp);
int			handle_heredoc_pipes(int argc, char **argv, char **envp);
int			handle_here_doc(char **argv);
int			init_fd(t_pipex *pipex, int argc, char **argv, int mode);
void		init_pipex(t_pipex *pipex, int argc);
int			duplicate(t_pipex *pipex, int mode);

#endif

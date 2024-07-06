/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 13:51:11 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/06 15:57:28 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		printf("use this format: ./pipex file1 cmd1 cmd2 file2\n");
	}
	else if (strncmp(argv[1], "here_doc", 8) == 0)
	{
		handle_here_doc(argv);
		argc--;
		handle_heredoc_pipes(argc, &argv[1], envp);
	}
	else
		handle_multiple_pipes(argc, argv, envp);
	return (EXIT_SUCCESS);
}

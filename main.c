/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:50:20 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/03/21 18:56:36 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void pipex_print_struct (px_list *pipex_list)
{
	size_t	i;

	i = 0;
	while (pipex_list != NULL)
	{
		printf("path: %s\nchild_n: %i\ncmd:\n", pipex_list->path, pipex_list->child_n);
		while (pipex_list->cmd[i] != NULL)
		{
			printf("%s\n", pipex_list->cmd[i]);
			i++;
		}
		pipex_list = pipex_list->next;
		i = 0;
	}
}

int	main(int ac, char **av, char **envp)
{
	px_list	*pipex_list;
	f_list	files;

	if (ac < 5)
	{
		printf("Arguments count error\n");
		return (0);
	}
	pipex_list = pipex_parse(ac, av, envp);
	if (open_files(ac, av, files) < 0)
	{
		
	}
	pipex_print_struct(pipex_list);
	free_pipex_struct(&pipex_list);
	return (0);
}

/*
	char			*infile;
	char			*outfile;
	char			**cmd;
	char			*path;
	int				*fd[2];
*/
/*
	infile = av[1];
	outfile = av[4];
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');

	int	i = 0;
	printf("%s\n", infile);
	printf("%s\n", outfile);
	while (cmd1[i] != NULL)
		printf("%s ", cmd1[i++]);
	i = 0;
	printf("\n");
	while (cmd2[i] != NULL)
		printf("%s ", cmd2[i++]);
	printf("\n");
*/
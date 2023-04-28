/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:50:20 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/04/28 17:26:22 by lsohler          ###   ########.fr       */
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

int	create_pipe(px_list **list)
{
	px_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		pipe(tmp->fd);
		tmp = tmp->next;
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	px_list	*pipex_list;
	px_list	*tmp;
	f_list	*files;

	/*if (ac < 5)
		exiterror("Arguments count error\n");*/
	pipex_list = pipex_parse(ac, av, envp);
	tmp = pipex_list;
	create_pipe(&pipex_list);
	if (open_files(ac, av, &files) > 0)
	{
		//printf("infile: %i\noutfile: %i\n", files->infile, files->outfile);
		while (pipex_list)
		{
			//printf("Test while\n");
			pipex_child(pipex_list, files, envp);
			printf("FD_IN: %i FD_OUT: %i\n", pipex_list->fd[0], pipex_list->fd[1]);
			pipex_list = pipex_list->next;
			//printf("Test while 2\n");
		}
	}
	waitpid(-1, NULL, 0);
	write(1, "Fin\n", 4);
	pipex_print_struct(tmp);
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
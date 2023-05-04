/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:50:20 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/05/04 15:06:51 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void pipex_print_struct (px_list *pipex_list)
{
	size_t	i;

	i = 0;
	while (pipex_list != NULL)
	{
		printf("FD[0] = %i FD[1] = %i\n", pipex_list->fd[0], pipex_list->fd[1]);
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
	create_pipe(&pipex_list);
	tmp = pipex_list;
	//pipex_print_struct(tmp);
	files = open_files(ac, av);
	if (files->open == 1)
	{
		//printf("infile: %i\noutfile: %i\n", files->infile, files->outfile);
		while (pipex_list)
		{
			//printf("Test while\n");
			//printf("FD_IN: %i FD_OUT: %i\n", pipex_list->fd[0], pipex_list->fd[1]);
			files->pid = fork();
			if (files->pid == 0)
				pipex_child(&pipex_list, &files, envp);
			pipex_list = pipex_list->next;
			//printf("Test while 2\n");
		}
	}
	//waitpid(-1, NULL, 0);
	//write(1, "Fin\n", 4);

	free_pipex_struct(&pipex_list);
	return (0);
}
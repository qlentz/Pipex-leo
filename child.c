/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:59:21 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/04/28 17:06:17 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*void	my_dup2(px_list *child)
{
		dup2();
		dup2();
		close();
}*/

void	pipex_child(px_list *child, f_list *file, char **envp)
{
	file->pid = fork();
	// printf("Test pipex_child: fork= %i\n", child->pid);
	// printf("infile: %i\noutfile: %i\n", file->infile, file->outfile);
	if (file->pid == 0)
	{
		if (child->child_n == 1)
		{
			//printf("Test pipex_child: 1\n");
			dup2(file->infile, 0);
			dup2(child->fd[1], 1);
		}
		else if (child->child_n == -1)
		{
			//printf("Test pipex_child: last\n");
			dup2(child->prev->fd[1], 0);
			dup2(file->outfile, 1);
		}
		else
		{
			//printf("Test pipex_child: x\n");
			dup2(child->prev->fd[1], 0);
			dup2(child->fd[0], 1);
		}
		//printf("FD_IN: %i FD_OUT: %i\n", child->fd[0], child->fd[1]);
		// close(child->prev->fd[0]);
		close(child->fd[0]);
		execve(child->path, child->cmd, envp);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:59:21 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/05/04 15:45:38 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*void	my_dup2(px_list *child)
{
		dup2();
		dup2();
		close();
}*/

void	pipex_child(px_list **child, f_list **file, char **envp)
{
	//printf("test\n");
	if ((*child)->child_n == 1)
	{
		dup2((*file)->infile, 0);
		dup2((*child)->fd[1], 1);
	}
	else if ((*child)->child_n == -1)
	{
		//printf("testlast\n");
		dup2((*child)->prev->fd[0], 0);
		dup2((*file)->outfile, 1);
	}
	else
	{
		dup2((*child)->prev->fd[0], 0);
		dup2((*child)->fd[1], 1);
	}
	execve((*child)->path, (*child)->cmd, envp);
	/*file->pid = fork();

	printf("FD_IN: %i FD_OUT: %i\n", (*child)->fd[0], (*child)->fd[1]);
	if (file->pid == 0)
	{
		if ((*child)->child_n == 1)
		{
			dup2(file->infile, 0);
			dup2((*child)->fd[1], 1);
		}
		else if ((*child)->child_n == -1)
		{
			dup2((*child)->prev->fd[0], 0);
			dup2(file->outfile, 1);
		}
		else
		{
			dup2((*child)->prev->fd[0], 0);
			//dup2((*child)->fd[1], 1);
		}
		execve((*child)->path, (*child)->cmd, envp);
	}*/
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:59:21 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/04/14 15:54:56 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	my_dup2(px_list *child)
{
		dup2();
		dup2();
		close();
}

void	pipex_child(px_list *child, f_list *file, char **envp)
{
	child->pid = fork();
	if (child->pid == -1)
		error_msg("fork error\n");
	if (child->child_n == 1)
	{
		dup2(file->infile, 0);
		dup2(child->fd[0], 1);
	}
	else if (child->child_n == -1)
	{
		dup2(child->prev->fd[1], 0);
		dup2(file->outfile, 1);
	}
	else
	{
		dup2(child->prev->fd[1], 0);
		dup2(child->fd[0], 1);
	}
	close(child->fd[0]);
	execve(child->path, child->cmd, envp);
}

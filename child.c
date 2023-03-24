/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:59:21 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/03/24 15:35:15 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_child(px_list *child)
{
	pid_t	pid;
	
	if (child->child_n == 1)
	{
		dup2
	}
	else if (child->child_n == -1)

	else
}

	while (*cmd != NULL) 
	{
		if ((pid = fork()) == -1) 
		{
			perror("fork");
			exit(1);
			}
		else if (pid == 0)
		{
		// if there is next
		if (*(cmd + 1) != NULL)
		{
			if (dup2(fd[j + 1], 1) < 0)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
		}
		// if there is previous
		if (j != 0)
		{
			if (dup2(fd[j - 2], 0) < 0)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
		}

      for (i = 0; i < 2 * cmd_len; i++) {
        close(fd[i]);
      }

      if (execvp((*cmd)[0], *cmd) < 0) {
        perror((*cmd)[0]);
        exit(EXIT_FAILURE);
      }
    } else if (pid < 0) {
      perror("error");
      exit(EXIT_FAILURE);
    }
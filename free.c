/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:29:09 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/04/28 11:46:54 by lsohler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_split(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
		free(array);
}

void	free_pipex_struct(px_list **list)
{
	px_list	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		//printf("test\n");
		if((*list)->path)
			free((*list)->path);
		if ((*list)->cmd)
			free_split((*list)->cmd);
		free(*list);
		*list = tmp;
		//printf("free test\n");
	}
}
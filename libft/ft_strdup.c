/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:51:37 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/01/30 12:31:43 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char    *ft_strdup(const char *s1)
{
		char    *s2;
        int             i;

        i = 0;
        s2 = malloc(sizeof(char) * ft_strlen(s1) + 1);
        if (!s2)
                return (NULL);
        while (s1[i] != '\0')
        {
                s2[i] = s1[i];
                i++;
        }
        s2[i] = '\0';
        return (s2);
}
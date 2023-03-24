/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsohler@student.42.fr <lsohler>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:52:00 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/03/21 18:56:50 by lsohler@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

# define STD_IN 0
# define STD_OUT 1 
# define STD_ERR 2

typedef	struct	s_list
{
	int				child_n;
	char			*infile;
	char			*outfile;
	char			**cmd;
	char			*path;
	int				*fd[2];
	pid_t			pid;
	struct	s_list	*next;
}				px_list;

typedef	struct	t_list
{
	int				**fd;
	int				infile;
	int				outfile;
	pid_t			pid;
}				f_list;

char	**ft_split(char *s, char c);
char	*ft_strdup(const char *s1);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	**pipex_path_array(char **envp);
char	*pipex_path(char *cmd, char **envp);
px_list	*pipex_lstnew(int ac, char **av, int i, char **envp);
px_list	*pipex_parse(int ac, char **av, char **envp);
void	free_pipex_struct(px_list **list);
void 	free_split(char **array);
int		open_files(int ac, char **av, f_list files);
int		error_msg(char *msg);




#endif
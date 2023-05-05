/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qlentz <qlentz@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:50:20 by lsohler@stu       #+#    #+#             */
/*   Updated: 2023/05/05 17:07:57 by qlentz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void execute_commands(px_list *commands, f_list *files, char **envp)
{
    int pipefd[2];
    int status;
    int prev_pipe_in = -1;
    pid_t wpid;
    px_list *current = commands;

    while (current)
    {
        if (current->next)
        {
            if (pipe(pipefd) < 0)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        current->pid = fork();
        if (current->pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (current->pid == 0) // Child process
        {
            if (current->prev == NULL) // First command
            {
                dup2(files->infile, STDIN_FILENO);
            }
            else
            {
                dup2(prev_pipe_in, STDIN_FILENO);
                close(prev_pipe_in);
            }

            if (current->next) // Not the last command
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
            }
            else
            {
                dup2(files->outfile, STDOUT_FILENO);
            }

            if (execve(current->path, current->cmd, envp) < 0)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else // Parent process
        {
            if (prev_pipe_in != -1)
            {
                close(prev_pipe_in);
            }

            if (current->next) // Not the last command
            {
                prev_pipe_in = pipefd[0];
                close(pipefd[1]);
            }
        }

        current = current->next;
    }

    if (prev_pipe_in != -1)
    {
        close(prev_pipe_in);
    }

    while ((wpid = wait(&status)) > 0); // Wait for all child processes to finish
}

int main(int argc, char **argv, char **envp)
{
    if (argc < 5)
    {
        fprintf(stderr, "Usage: %s file1 cmd1 cmd2 ... cmdn file2\n", argv[0]);
        return 1;
    }

    f_list *files = open_files(argc, argv);
    px_list *commands = pipex_parse(argc, argv, envp);

    execute_commands(commands, files, envp);

    free_pipex_struct(&commands);
    close(files->infile);
    close(files->outfile);
    free(files);

    return 0;
}
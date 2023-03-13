/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:49:04 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/10 16:11:50 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"

char	*ft_find_path(char *path, char *command)
{
	char	**path_split;
	char	*path_command;
	int		i;

	i = 0;
	command = ft_strjoin("/",command);
	path_split = ft_split(path, ':');
	while (path_split[i])
	{
		path_command = ft_strjoin(path_split[i], command);
		if (access(path_command, X_OK) == 0)
			break;
		free(path_command);
		i++;
	}
	i = 0;
	while (path_split[i])
	{
		free(path_split[i]);
		i++;
	}
	free(path_split);
	free(command);
	return (path_command);
}


int main(int argc, char **argv, char **envp)
{
	if (argc == 10)
		return(10);
	char *flags1[] = {"pipex", "-la", NULL};
	// char *flags1[] = {"ping", "-c", "5", "google.com", NULL};
	char *flags2[] = {"pipex", "-l", NULL};
	int p1[2]; // c -> p
	if(pipe(p1) == -1)
		return 1; 
	int pid1 = fork();
	if (pid1 < 0)
		return 2;
	if (pid1 == 0)
	{
		dup2(p1[1], STDOUT_FILENO);
		close(p1[0]);
		close(p1[1]);
		execve(ft_find_path(envp [5], argv[1]), flags1, NULL);
	}
	int pid2 = fork();
	if (pid2 < 0)
		return 2;
	if (pid2 == 0)
	{
		dup2(p1[0], STDIN_FILENO);
		close(p1[0]);
		close(p1[1]);
		execve(ft_find_path(envp [5], argv[2]), flags2, NULL);
	}
	close(p1[0]);
	close(p1[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
} 

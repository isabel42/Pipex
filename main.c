/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:49:04 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/13 16:51:26 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"

char	*ft_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*ft_find_path(char *path, char *command)
{
	char	**path_split;
	char	*path_command;
	int		i;

	i = 0;
	command = ft_strjoin("/", command);
	path_split = ft_split(path, ':');
	while (path_split[i])
	{
		path_command = ft_strjoin(path_split[i], command);
		if (access(path_command, X_OK) == 0)
			break ;
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

char	*ft_command (char **argv, int i)
{
	char	**command_flags;
	char	*command;
	int		j;

	j = 0;
	command_flags = ft_split(argv[i + 1], ' ');
	command = command_flags[0];
	while (command_flags[j])
	{
		free(command_flags[j]);
		j++;
	}
	free(command_flags);
	return(command);
}

char	*ft_flags (char **argv, int i)
{
	char	**command_flags;
	char	*command;
	char	*flags;
	int		j;

	j = 0;
	command_flags = ft_split(argv[i + 1], ' ');
	command = command_flags[0];
	flags = ft_strtrim(argv[i + 1], command);
	flags = ft_strtrim(flags, " ");
	while (command_flags[j])
	{
		free(command_flags[j]);
		j++;
	}
	free(command_flags);
	printf("flags:%s\n", flags);
	return(flags);
}


int	main(int argc, char **argv, char **envp)
{
	char	*flags1[] = {"pipex", "-la", NULL};
	char	*flags2[] = {"pipex", "-l", NULL};
	int		p1[2];

	if (argc == 10)
		return (10);
	if (pipe(p1) == -1)
		return 1;
	int	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		dup2(p1[1], STDOUT_FILENO);
		close(p1[0]);
		close(p1[1]);
		execve(ft_find_path(ft_path(envp), argv[1]), flags1, NULL);
	}
	int pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0)
	{
		dup2(p1[0], STDIN_FILENO);
		close(p1[0]);
		close(p1[1]);
		execve(ft_find_path(ft_path(envp), argv[2]), flags2, NULL);
	}
	close(p1[0]);
	close(p1[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
} 

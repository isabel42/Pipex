/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:49:04 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/14 22:20:57 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"

void	ft_free_cc(char **split)
{
	int i;
	
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*ft_envp(char **envp, char *pwd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], pwd, ft_strlen(pwd)) == 0)
			return (envp[i] + ft_strlen(pwd));
		i++;
	}
	return (NULL);
}

char	*ft_find_pwd(char *pwd, char *infile)
{
	char	*pwd_infile;

	infile = ft_strjoin("/", infile);
	pwd_infile = ft_strjoin(pwd, infile);
	if (access(pwd_infile, R_OK) == 0)
	{
		free(infile);
		return (pwd_infile);
	}
	free(infile);
	free(pwd_infile);
	perror("zsh");
	exit(0);
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
		{
			ft_free_cc(path_split);
			free(command);
			return (path_command);
		}
		free(path_command);
		i++;
	}
	ft_free_cc(path_split);
	free(command);
	return(NULL);
}

char	*ft_command (char **argv, int i)
{
	char	*command;
	int		j;

	j = 0;
	while(argv[i + 1][j] != ' ')
		j++;
	command = ft_calloc(j + 1, sizeof(command));
	j--;
	while (j >= 0)
	{
		command[j] = argv[i + 1][j];
		j--;
	}
	return(command);
}

char	*ft_flags (char **argv, int i)
{
	char	*flags;
	int		j;

	j = 0;
	while (argv[i + 1][j] != ' ')
		j++;
	flags = argv[i + 1] + j + 1;
	return (flags);
}


int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (0);

	char *path = ft_envp(envp, "PATH=");
	char *pwd = ft_envp(envp, "PWD=");

	char	*command1 = ft_command (argv, 1);
	char	*command2 = ft_command (argv, 2);
	char	*flags1[] = {"pipex", ft_flags(argv, 1), NULL};
	char	*flags2[] = {"pipex",  ft_flags(argv, 2), NULL};
	char	*pathname1 = ft_find_path(path, command1);
	char	*pathname2 = ft_find_path(path, command2);
	char	*pathinfile = ft_find_pwd(pwd, argv[1]);
	char	*pathoutfile = ft_find_pwd(pwd, argv[4]);

	int		p1[2];
	if (pipe(p1) == -1)
		return 1;
	int	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		p1[0] = open (pathinfile, O_RDONLY);
		dup2(p1[0], STDIN_FILENO);
		dup2(p1[1], STDOUT_FILENO);
		close(p1[0]);
		close(p1[1]);
		execve(pathname1, flags1, NULL);
	}
	int pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0)
	{
		int a = open (pathoutfile, O_TRUNC | O_CREAT | O_RDWR);
		dup2(p1[0], STDIN_FILENO);
		dup2(a, STDOUT_FILENO);
		close(p1[0]);
		close(p1[1]);
		execve(pathname2, flags2, NULL);
	}
	close(p1[0]);
	close(p1[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free(command1);
	free(command2);
	free(pathname1);
	free(pathname2);
	free(pathinfile);
	free(pathoutfile);
	
	return (0);
} 

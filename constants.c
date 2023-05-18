/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:19:45 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/18 17:34:06 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

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
	free(infile);
	return (pwd_infile);
}

void	ft_perror_comm(char *command, char *infile)
{
	int	a;

	if (infile != NULL)
	{
		a = open (infile, O_RDONLY | O_CLOEXEC);
		if (a >= 0)
		{
			ft_putstr_fd("Command not found: ", 1);
			if (command)
				ft_putstr_fd(command, 1);
			ft_putstr_fd("\n", 1);
		}
		else
			ft_putstr_fd("No such file or directory\n", 1);
		close (a);
	}
	else
	{
		ft_putstr_fd("Command not found: ", 1);
		if (command)
			ft_putstr_fd(command, 1);
		ft_putstr_fd("\n", 1);
	}
}

char	*ft_find_path(char *path, char *command, char *infile)
{
	char	**path_split;
	char	*path_command;
	char	*slash_command;
	int		i;

	i = 0;
	if (command)
	{
		slash_command = ft_strjoin("/", command);
		path_split = ft_split(path, ':');
		while (path_split[i])
		{
			path_command = ft_strjoin(path_split[i], slash_command);
			if (access(path_command, X_OK) == 0)
			{
				ft_free_cc_c(path_split, slash_command);
				return (path_command);
			}
			free(path_command);
			i++;
		}
		ft_free_cc_c(path_split, slash_command);
	}
	ft_perror_comm(command, infile);
	return (NULL);
}

char	**ft_flags(char **argv, int i)
{
	char	**flags;
	char	*only_flag;
	int		j;

	flags = malloc(sizeof(flags) * 3);
	if (!flags)
		exit(0);
	j = 0;
	while (argv[i + 1][j] != ' ' && argv[i + 1][j] != '\0')
		j++;
	if (argv[i + 1][j] == '\0')
		only_flag = NULL;
	else
	{
		while (argv[i + 1][j] == ' ')
			j++;
		if (argv[i + 1][j] == '\0')
			only_flag = NULL;
		else
			only_flag = argv[i + 1] + j;
	}
	flags[0] = argv[0];
	flags[1] = only_flag;
	flags[2] = NULL;
	return (flags);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:19:45 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/16 14:54:35 by itovar-n         ###   ########.fr       */
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

char	*ft_find_path(char *path, char *command)
{
	char	**path_split;
	char	*path_command;
	char	*slash_command;
	int		i;

	i = 0;
	slash_command = ft_strjoin("/", command);
	path_split = ft_split(path, ':');
	while (path_split[i])
	{
		path_command = ft_strjoin(path_split[i], slash_command);
		if (access(path_command, X_OK) == 0)
		{
			ft_free_cc(path_split);
			free(slash_command);
			return (path_command);
		}
		free(path_command);
		i++;
	}
	ft_free_cc(path_split);
	free(slash_command);
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
    if (!command)
        exit(0);
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

char **ft_param (char **argv, char **envp, int argc)
{
	char	**command;
	char	**param;
	char	*flags;
	char	*pathname;
	char	*pathinfile;
	char	*pathoutfile;

	param = malloc(sizeof(param) * 5);
	if(!param)
		exit(0);
	command = ft_split(argv[argc + 1], ' ');
	flags = ft_flags(argv, argc);
	pathname = ft_find_path(ft_envp(envp, "PATH="), command[0]);
	pathinfile = ft_find_pwd(ft_envp(envp, "PWD="), argv[1]);
	pathoutfile = ft_find_pwd(ft_envp(envp, "PWD="), argv[4]);
	param[0] = flags;
	param[1] = pathname;
	param[2] = pathinfile;
	param[3] = pathoutfile;
	param[4] = argv[0];
	ft_free_cc(command);
	return(param);
}
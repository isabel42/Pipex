/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:19:45 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/15 18:12:15 by itovar-n         ###   ########.fr       */
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
			free(command);
			free(slash_command);
			return (path_command);
		}
		free(path_command);
		i++;
	}
	ft_free_cc(path_split);
	free(command);
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

t_param *ft_param(char **argv, char **envp, int i)
{
    t_param	*elem;
    char	*path;
	char	*pwd;
    char	*command;

    elem = malloc(sizeof(elem) * 1);
	if (!elem)
		exit(0);
	path = ft_envp(envp, "PATH=");
	pwd = ft_envp(envp, "PWD=");
    command = ft_command (argv, i);
	
	elem->pathname = ft_find_path(path, command);
	elem->pathinfile = ft_find_pwd(pwd, argv[1]);
	elem->pathoutfile = ft_find_pwd(pwd, argv[4]);
    free(command);

    return(elem);
}

char **ft_param (char **param, char **argv, char **envp)
{
	char	*command;
	char	*pathinfile = ft_find_pwd(ft_envp(envp, "PWD="), argv[1]);
	char	*pathname1 = ft_find_path(ft_envp(envp, "PATH="), ft_command (argv, 1));
	char	*flags1;

	command = ft_command (argv, 1);
	pathinfile = ft_find_pwd(ft_envp(envp, "PWD="), argv[1]);
	pathname1 = ft_find_path(ft_envp(envp, "PATH="), ft_command (argv, 1));
	flags1 = ft_flags(argv, 1);

}
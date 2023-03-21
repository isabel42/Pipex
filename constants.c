/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:19:45 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/21 15:26:26 by itovar-n         ###   ########.fr       */
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

char	*ft_find_shell(char **envp)
{
	char	*envp_shell;
	char	**shell;
	char	*sol;
	int		j;
	int		i;

	envp_shell = ft_envp(envp, "SHELL=");
	shell = ft_split(envp_shell, '/');
	j = 0;
	i = 0;
	while (shell[j])
		j++;
	if (j == 0)
		return (NULL);
	j--;
	sol = ft_calloc(sizeof(sol), (ft_strlen(shell[j]) + 1));
	while (shell[j][i] != '\0')
	{
		sol[i] = shell[j][i];
		i++;
	}
	ft_free_cc(shell);
	return (sol);
}

char	*ft_find_path(char *path, char *command, char **envp)
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
	printf("%s: command not found: %s\n", ft_find_shell(envp), command);
	return (NULL);
}

char	**ft_flags(char **argv, int i)
{
	char	**flags;
	int		j;

	flags = malloc(sizeof(flags) * 3);
	if (!flags)
		exit(0);
	j = 0;
	while (argv[i + 1][j] != ' ' && argv[i + 1][j] != '\0')
		j++;
	if (j == (int)ft_strlen(argv[i + 1]))
		return (NULL);
	flags[0] = argv[0];
	flags[1] = argv[i + 1] + j + 1;
	flags[2] = NULL;
	return (flags);
}

char	**ft_param(int argc, char **argv, char **envp, int i)
{
	char	**command;
	char	**param;
	char	*pathinfile;
	char	*pathoutfile;

	param = malloc(sizeof(param) * 7);
	if (!param)
		exit(0);
	command = ft_split(argv[i + 1], ' ');
	pathinfile = NULL;
	if (i == 1)
		pathinfile = ft_find_pwd(ft_envp(envp, "PWD="), argv[i]);
	pathoutfile = NULL;
	if (i == argc - 3)
		pathoutfile = ft_find_pwd(ft_envp(envp, "PWD="), argv[argc - 1]);
	param[0] = NULL;
	param[1] = ft_find_path(ft_envp(envp, "PATH="), command[0], envp);
	param[2] = pathinfile;
	param[3] = pathoutfile;
	param[4] = argv[0];
	param[5] = ft_find_shell(envp);
	param[6] = ft_itoa(argc);
	ft_free_cc(command);
	return (param);
}

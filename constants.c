/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:19:45 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/15 13:38:04 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_find_pwd(char *pwd, char *infile, int i)
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
	if (i == 1)
		perror("zsh");
	return (pwd_infile);
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

t_param ft_param(char **argv, char **envp, int i)
{
    t_param	*elem;
    char	*path;
	char	*pwd;
    char	*command;

    path = ft_envp(envp, "PATH=");
	pwd = ft_envp(envp, "PWD=");
    command = ft_command (argv, i);
    
	elem->command = command;
	elem->flags[] = {"pipex", ft_flags(argv, i), NULL};
	elem->pathname = ft_find_path(path, command);
	elem->pathinfile = ft_find_pwd(pwd, argv[1], i);
	elem->pathoutfile = ft_find_pwd(pwd, argv[4], i);
    elem->path = path;
	elem->pwd = pwd;

    return(elem);
}
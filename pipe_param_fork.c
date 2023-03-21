/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_param_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:30:21 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/21 16:06:44 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

int	**ft_pipe(int argc)
{
	int		**p1;
	int		i;

	i = 0;
	if (argc == 4)
		p1 = malloc(sizeof(p1) * 1);
	else
		p1 = malloc(sizeof(p1) *(argc - 4));
	while (i < (argc - 4) || i == 0)
	{
		p1[i] = malloc(sizeof(p1) * 2);
		if (pipe(p1[i]) == -1)
			exit (1);
		i++;
	}
	return (p1);
}

void	ft_closepipe(int **p1, int argc)
{
	int	i;

	i = 0;
	while (i < (argc - 4) || i == 0)
	{
		close(p1[i][0]);
		close(p1[i][1]);
		i++;
	}
}

void	ft_waitpid(int *pid)
{
	int	i;

	i = 0;
	while (pid[i])
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

char	**ft_param(int argc, char **argv, char **envp, int i)
{
	char	**command;
	char	**param;
	char	*pathinfile;
	char	*pathoutfile;

	param = malloc(sizeof(param) * 6);
	if (!param)
		exit(0);
	command = ft_split(argv[i + 1], ' ');
	pathinfile = NULL;
	if (i == 1)
		pathinfile = ft_find_pwd(ft_envp(envp, "PWD="), argv[i]);
	pathoutfile = NULL;
	if (i == argc - 3)
		pathoutfile = ft_find_pwd(ft_envp(envp, "PWD="), argv[argc - 1]);
	param[0] = ft_find_path(ft_envp(envp, "PATH="), command[0], envp);
	param[1] = pathinfile;
	param[2] = pathoutfile;
	param[3] = argv[0];
	param[4] = ft_find_shell(envp);
	param[5] = ft_itoa(argc);
	ft_free_cc(command);
	return (param);
}

void	ft_fork(char **param, int **p1, char **flags, int i)
{
	int		a;
	int		b;

	if (param[1] != NULL)
	{
		a = open (param[1], O_RDONLY | O_CLOEXEC);
		if (a < 0 && param[0] != NULL)
			perror(param[4]);
	}
	else
		a = p1[i - 1][0];
	if (param[2] != NULL)
		b = open (param[2], O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 00777);
	else
		b = p1[i][1];
	dup2(a, STDIN_FILENO);
	dup2(b, STDOUT_FILENO);
	ft_closepipe(p1, ft_atoi(param[5]));
	execve(param[0], flags, NULL);
}

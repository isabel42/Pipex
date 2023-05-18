/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:30:21 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/18 17:38:04 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

int	**ft_pipe(int argc)
{
	int		**p1;
	int		i;

	i = 0;
	if (argc == 4)
	{
		p1 = malloc(sizeof(p1) * 1);
		if (!p1)
			exit(0);
	}
	else
	{
		p1 = malloc(sizeof(p1) * (argc - 4));
		if (!p1)
			exit(0);
	}
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

void	ft_fork(char **param, int **p1, char **flags, int i)
{
	int		a;
	int		b;

	if (param[1] != NULL && param[0] != NULL)
	{
		a = open (param[1], O_RDONLY | O_CLOEXEC);
		if (a < 0)
		{
			perror(NULL);
			a = p1[i - 1][0];
		}
	}
	else
		a = p1[i - 1][0];
	if (param[2] != NULL)
		b = open (param[2], O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 00644);
	else
		b = p1[i][1];
	dup2(a, STDIN_FILENO);
	dup2(b, STDOUT_FILENO);
	close (a);
	ft_closepipe(p1, ft_atoi(param[4]));
	execve(param[0], flags, NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:45:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/21 08:32:07 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

void	ft_free_cc(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_param(char **param)
{
	free(param[1]);
	free(param[2]);
	free(param[3]);
	free(param[5]);
	free(param);
}

void	ft_fork(char **param1, int pid1, int *p1)
{
	char	**flags1;

	flags1 = malloc(sizeof(flags1) * 3);
	if (!flags1)
		exit(0);
	flags1[0] = param1[4];
	flags1[1] = param1[0];
	flags1[2] = NULL;
	if (pid1 < 0)
		exit (2);
	if (pid1 == 0)
	{
		p1[0] = open (param1[2], O_RDONLY | O_CLOEXEC);
		if (p1[0] < 0 && param1[1] != NULL)
			perror(param1[5]);
		else if (p1[0] >= 0)
		{
			dup2(p1[0], STDIN_FILENO);
			dup2(p1[1], STDOUT_FILENO);
			close(p1[0]);
			close(p1[1]);
			execve(param1[1], flags1, NULL);
		}
		close(p1[0]);
		close(p1[1]);
		exit(0);
	}
	free(flags1);
}

void	ft_fork2(char **param2, int pid2, int *p1)
{
	char	**flags2;
	int		a;

	flags2 = malloc(sizeof(flags2) * 3);
	if (!flags2)
		exit(0);
	flags2[0] = param2[4];
	flags2[1] = param2[0];
	flags2[2] = NULL;
	if (pid2 < 0)
		exit (2);
	if (pid2 == 0)
	{
		a = open (param2[3], O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 00777);
		dup2(p1[0], STDIN_FILENO);
		dup2(a, STDOUT_FILENO);
		close(p1[0]);
		close(p1[1]);
		execve(param2[1], flags2, NULL);
	}
	free(flags2);
}


void	ft_fork_final(char **param, int **p1, char **flags, int i)
{
	int		a;
	int		j;

	j = 0;
	if (i > 0)
	{
		i--;
		printf("i: %d\n", i);
	}
		printf("Param2: %s\n", param[2]);
	if (param[2] != NULL)
	{
		p1[i][0] = open (param[2], O_RDONLY | O_CLOEXEC);
		if (p1[i][0] < 0 && param[1] != NULL)
			perror(param[5]);
	}
	if (param[3] != NULL)
	{
		a = open (param[3], O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 00777);
	}
	else
	{
		a = p1[i][1];
	}
	dup2(p1[i][0], STDIN_FILENO);
		printf("a: %d\n", a);
	dup2(a, STDOUT_FILENO);
	while (p1[j])
	{
		close(p1[j][0]);
		close(p1[j][1]);
		j++;	
	}
	execve(param[1], flags, NULL);
}

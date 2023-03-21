/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:45:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/21 15:13:47 by itovar-n         ###   ########.fr       */
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

void	ft_free_ii(int **split, int j)
{
	int	i;

	i = 0;
	while (i < j)
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
	free(param[6]);
	free(param);
}

void	ft_fork(char **param, int **p1, char **flags, int i)
{
	int		a;
	int		b;
	int		j;

	if (param[2] != NULL)
	{
		a = open (param[2], O_RDONLY | O_CLOEXEC);
		if (a < 0 && param[1] != NULL)
			perror(param[5]);
	}
	else
		a = p1[i - 1][0];
	if (param[3] != NULL)
		b = open (param[3], O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 00777);
	else
		b = p1[i][1];
	dup2(a, STDIN_FILENO);
	dup2(b, STDOUT_FILENO);
	j = -1;
	while (++j < (ft_atoi(param[6]) - 4) || ++j == 0)
	{
		close(p1[j][0]);
		close(p1[j][1]);
	}
	execve(param[1], flags, NULL);
}

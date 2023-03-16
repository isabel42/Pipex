/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:45:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/16 14:55:00 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

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

void	ft_free_param(char **param)
{
	free(param[1]);
	free(param[2]);
	free(param[3]);
	free(param);
	
}

void ft_fork(char **param1, int pid1, int *p1)
{
	char	*flags1[] = {param1[4], param1[0], NULL};
	if (pid1 == 0)
	{
		p1[0] = open (param1[2], O_RDONLY | O_CLOEXEC);
		if (p1[0] < 0)
			perror("zsh");
		else
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
}
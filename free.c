/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:45:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/15 18:00:18 by itovar-n         ###   ########.fr       */
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

void ft_free_param (t_param *elem)
{
	free(elem->pathname);
	free(elem->pathinfile);
	free(elem->pathoutfile);
	free(elem);
}

void ft_fork(int pid, char **argv, char **envp, int *p1)
{
	char	*pathinfile = ft_find_pwd(ft_envp(envp, "PWD="), argv[1]);
	char	*pathname1 = ft_find_path(ft_envp(envp, "PATH="), ft_command (argv, 1));
	char	*flags1[] = {argv[0], ft_flags(argv, 1), NULL};

	if (pid == 0)
	{
		p1[0] = open (pathinfile, O_RDONLY | O_CLOEXEC);
		if (p1[0] < 0)
			perror("zsh");
		else
		{
			dup2(p1[0], STDIN_FILENO);
			dup2(p1[1], STDOUT_FILENO);
			close(p1[0]);
			close(p1[1]);
			execve(pathname1, flags1, NULL);
		}
		close(p1[0]);
		close(p1[1]);
		return(0);
	}
}
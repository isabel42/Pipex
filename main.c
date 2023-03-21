/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:49:04 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/21 15:25:39 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**param;
	char	**flags;
	int		*pid;
	int		**p1;
	int		i;

	i = 0;
	pid = malloc(sizeof(pid) *(argc - 3));
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
	i = 0;
	while (i < (argc - 3))
	{
		param = ft_param(argc, argv, envp, i + 1);
		flags = ft_flags(argv, i + 1);
		pid[i] = fork();
		if (pid[i] == 0)
			ft_fork(param, p1, flags, i);
		ft_free_param(param);
		free(flags);
		i++;
	}
	i = 0;
	while (i < (argc - 4) || i == 0)
	{
		close(p1[i][0]);
		close(p1[i][1]);
		i++;
	}
	i = 0;
	while (pid[i])
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	ft_free_ii(p1, i - 1);
	free(pid);
	return (0);
}

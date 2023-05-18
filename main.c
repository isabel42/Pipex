/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:49:04 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/18 15:27:02 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

void	ft_free_loop(char **param, char **flags)
{
	ft_free_param(param);
	free(flags);
}

void	ft_checkarg(int argc)
{
	if (argc < 4)
	{
		ft_putstr_fd("Not enough arguments\n", 1);
		exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**param;
	char	**flags;
	int		*pid;
	int		**p1;
	int		i;

	ft_checkarg(argc);
	pid = malloc(sizeof(pid) *(argc - 3));
	p1 = ft_pipe(argc);
	i = 0;
	while (i < (argc - 3))
	{
		param = ft_param(argc, argv, envp, i + 1);
		flags = ft_flags(argv, i + 1);
		pid[i] = fork();
		if (pid[i] == 0)
			ft_fork(param, p1, flags, i);
		ft_free_loop(param, flags);
		i++;
	}
	ft_closepipe(p1, argc);
	ft_waitpid(pid);
	ft_free_ii(p1, i - 1);
	free(pid);
	return (0);
}

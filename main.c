/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:49:04 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/21 18:46:54 by itovar-n         ###   ########.fr       */
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

	pid = ft_calloc(sizeof(pid), (argc - 3));
	p1 = ft_pipe(argc);
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
	ft_closepipe(p1, argc);
	ft_waitpid(pid);
	ft_free_ii(p1, i - 1);
	free(pid);
	return (0);
}

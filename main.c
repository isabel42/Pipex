/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:49:04 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/21 08:32:40 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	char	**param1;
// 	char	**param2;
// 	int		pid1;
// 	int		pid2;
// 	int		p1[2];

// 	param1 = ft_param(argc, argv, envp, 1);
// 	param2 = ft_param(argc, argv, envp, 2);
// 	if (pipe(p1) == -1)
// 		return (1);
// 	pid1 = fork();
// 	ft_fork(param1, pid1, p1);
// 	pid2 = fork();
// 	ft_fork2(param2, pid2, p1);
// 	close(p1[0]);
// 	close(p1[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	ft_free_param(param1);
// 	ft_free_param(param2);
// 	return (0);
// }

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
		flags = ft_flags_final(param);
		pid[i] = fork();

		if(pid[i] == 0)
			ft_fork_final(param, p1, flags, i);
	printf("param2 - i - pid : %s - %d - %d \n", param[2], i, pid[i]);
		// waitpid(pid[i], NULL, 0);
		ft_free_param(param);
		free(flags);
		i++;
	}
	i = 0;
	while (p1[i])
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
	return (0);
}
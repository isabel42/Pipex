/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:49:04 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/16 15:35:32 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"


int	main(int argc, char **argv, char **envp)
{
	char	**param1;
	char	**param2;
	int		p1[2];

	param1 = ft_param (argc, argv, envp, 1);
	param2 = ft_param (argc, argv, envp, 2);
	if (pipe(p1) == -1)
		return 1;
	int	pid1 = fork();
	ft_fork(param1, pid1, p1);
	int pid2 = fork();
	ft_fork2(param2, pid2, p1);
	close(p1[0]);
	close(p1[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	ft_free_param(param1);
	ft_free_param(param2);
	return (0);
} 

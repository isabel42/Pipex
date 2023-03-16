/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:49:04 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/16 16:42:04 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"


int	main(int argc, char **argv, char **envp)
{
	t_param *param1;
	t_param *param2;
	int		p1[2];

	param1 = ft_param_s(argc, argv, envp, 1);
	param2 = ft_param_s(argc, argv, envp, 2);
	if (pipe(p1) == -1)
		return 1;
	int	pid1 = fork();
	ft_fork_s(param1, pid1, p1);
	int pid2 = fork();
	ft_fork2_s(param2, pid2, p1);
	close(p1[0]);
	close(p1[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	// ft_free_param(param1);
	// ft_free_param(param2);
	return (0);
} 

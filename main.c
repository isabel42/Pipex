/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:49:04 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/16 14:53:16 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"


int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (0);
	char	**param1;
	char	**param2;
	param1 = ft_param (argv, envp, 1);
	param2 = ft_param (argv, envp, 2);
	
	// char	*flags1[] = {argv[0], param1[0], NULL};
	char	*flags2[] = {argv[0],  param2[0], NULL};

	int		p1[2];
	if (pipe(p1) == -1)
		return 1;
	int	pid1 = fork();
	if (pid1 < 0)
		return (2);
	ft_fork(param1, pid1, p1);
	// if (pid1 == 0)
	// {
	// 	p1[0] = open (param1[2], O_RDONLY | O_CLOEXEC);
	// 	if (p1[0] < 0)
	// 		perror("zsh");
	// 	else
	// 	{
	// 		dup2(p1[0], STDIN_FILENO);
	// 		dup2(p1[1], STDOUT_FILENO);
	// 		close(p1[0]);
	// 		close(p1[1]);
	// 		execve(param1[1], flags1, NULL);
	// 	}
	// 	close(p1[0]);
	// 	close(p1[1]);
	// 	return(0);
	// }
	int pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0)
	{
		int a = open (param2[3], O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 00777);
		dup2(p1[0], STDIN_FILENO);
		dup2(a, STDOUT_FILENO);
		close(p1[0]);
		close(p1[1]);
		execve(param2[1], flags2, NULL);
	}
	close(p1[0]);
	close(p1[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	ft_free_param(param1);
	ft_free_param(param2);
	return (0);
} 

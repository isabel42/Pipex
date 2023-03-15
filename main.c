/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:49:04 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/15 15:20:12 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"


int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (0);

	t_param *first;
	t_param *second;

	first = ft_param(argv, envp, 1);
	second = ft_param(argv, envp, 2);
	// char *path = ft_envp(envp, "PATH=");
	// char *pwd = ft_envp(envp, "PWD=");

	// char	*command1 = ft_command (argv, 1);
	// char	*command2 = ft_command (argv, 2);
	// char	*flags1[] = {"pipex", ft_flags(argv, 1), NULL};
	// char	*flags2[] = {"pipex",  ft_flags(argv, 2), NULL};
	// char	*pathname1 = ft_find_path(path, command1);
	// char	*pathname2 = ft_find_path(path, command2);
	// char	*pathinfile = ft_find_pwd(pwd, argv[1], 1);
	// char	*pathoutfile = ft_find_pwd(pwd, argv[4], 2);

	int		p1[2];
	if (pipe(p1) == -1)
		return 1;
	int	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		p1[0] = open (first.pathinfile, O_RDONLY | O_CLOEXEC);
		if (p1[0] > 0)
		{
			dup2(p1[0], STDIN_FILENO);
			dup2(p1[1], STDOUT_FILENO);
			close(p1[0]);
			close(p1[1]);
			execve(first.pathname, first.flags, NULL);
		}
		close(p1[0]);
		close(p1[1]);
		return(0);
	}
	int pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0)
	{
		int a = open (first.pathoutfile, O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 00777);
		dup2(p1[0], STDIN_FILENO);
		dup2(a, STDOUT_FILENO);
		close(p1[0]);
		close(p1[1]);
		execve(second.pathname, second.flags, NULL);
	}
	close(p1[0]);
	close(p1[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	// free(command1);
	// free(command2);
	// free(pathname1);
	// free(pathname2);
	// free(pathinfile);
	// free(pathoutfile);
	ft_free_param(first);
	ft_free_param(second);
	return (0);
} 

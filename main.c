/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:49:04 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/15 18:12:15 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

char	*ft_flags (char **argv, int i)
{
	char	*flags;
	int		j;

	j = 0;
	while (argv[i + 1][j] != ' ')
		j++;
	flags = argv[i + 1] + j + 1;
	return (flags);
}
int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (0);
	char	**param = malloc(sizeof(param) * 4);
	if(!param)
		return(NULL);
	
	char	*flags1[] = {argv[0], ft_flags(argv, 1), NULL};
	char	*flags2[] = {argv[0],  ft_flags(argv, 2), NULL};
	char	*pathname1 = ft_find_path(ft_envp(envp, "PATH="), ft_command (argv, 1));
	char	*pathname2 = ft_find_path(ft_envp(envp, "PATH="), ft_command (argv, 2));
	char	*pathinfile = ft_find_pwd(ft_envp(envp, "PWD="), argv[1]);
	char	*pathoutfile = ft_find_pwd(ft_envp(envp, "PWD="), argv[4]);

	int		p1[2];
	if (pipe(p1) == -1)
		return 1;
	int	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
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
	int pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0)
	{
		int a = open (pathoutfile, O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 00777);
		dup2(p1[0], STDIN_FILENO);
		dup2(a, STDOUT_FILENO);
		close(p1[0]);
		close(p1[1]);
		execve(pathname2, flags2, NULL);
	}
	close(p1[0]);
	close(p1[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free(pathname1);
	free(pathname2);
	free(pathinfile);
	free(pathoutfile);
	// ft_free_param(first);
	// ft_free_param(second);
	return (0);
} 

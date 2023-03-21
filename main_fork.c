/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:29:21 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/21 18:38:39 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"


void	ft_fork(char **param, int **p1, char **flags, int i)
{
	int		a;
	int		b;

	if (param[1] != NULL)
	{
		a = open (param[1], O_RDONLY | O_CLOEXEC);
		if (a < 0 && param[0] != NULL)
			perror(param[4]);
	}
	else
		a = p1[i - 1][0];
	if (param[2] != NULL)
		b = open (param[2], O_TRUNC | O_CREAT | O_WRONLY | O_CLOEXEC, 00777);
	else
		b = p1[i][1];
	dup2(a, STDIN_FILENO);
	dup2(b, STDOUT_FILENO);
	ft_closepipe(p1, ft_atoi(param[5]));
	execve(param[0], flags, NULL);
}

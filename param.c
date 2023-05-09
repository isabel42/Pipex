/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:29:21 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/09 15:16:10 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

char	**ft_param(int argc, char **argv, char **envp, int i)
{
	char	**command;
	char	**param;
	char	*pathinfile;
	char	*pathoutfile;

	param = malloc(sizeof(param) * 5);
	if (!param)
		exit(0);
	command = ft_split(argv[i + 1], ' ');
	pathinfile = NULL;
	if (i == 1)
		pathinfile = ft_find_pwd(ft_envp(envp, "PWD="), argv[i]);
	pathoutfile = NULL;
	if (i == argc - 3)
		pathoutfile = ft_find_pwd(ft_envp(envp, "PWD="), argv[argc - 1]);
	param[0] = ft_find_path(ft_envp(envp, "PATH="), command[0], pathinfile);
	param[1] = pathinfile;
	param[2] = pathoutfile;
	param[3] = argv[0];
	param[4] = ft_itoa(argc);
	ft_free_cc(command);
	return (param);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:08:08 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/15 17:42:37 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPIPEX_H
# define LIBPIPEX_H
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"

typedef struct s_param
{
    char    *pathname;
	char    *pathinfile;
    char    *pathoutfile;
}   t_param;

char	*ft_envp(char **envp, char *pwd);
char	*ft_find_pwd(char *pwd, char *infile);
char	*ft_find_path(char *path, char *command);
char	*ft_command (char **argv, int i);
t_param *ft_param(char **argv, char **envp, int i);

void	ft_free_cc(char **split);
void ft_free_param (t_param *elem);

#endif
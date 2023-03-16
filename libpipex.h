/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:08:08 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/16 14:52:23 by itovar-n         ###   ########.fr       */
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

char	*ft_envp(char **envp, char *pwd);
char	*ft_find_pwd(char *pwd, char *infile);
char	*ft_find_path(char *path, char *command);
char	*ft_command (char **argv, int i);
char	*ft_flags (char **argv, int i);
char **ft_param (char **argv, char **envp, int argc);

void	ft_free_cc(char **split);
void  ft_free_param (char **param);
void ft_fork(char **param, int pid, int *p1);

#endif
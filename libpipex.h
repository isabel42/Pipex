/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:08:08 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/15 15:19:56 by itovar-n         ###   ########.fr       */
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
    char    **flags;
    char    *pathname;
	char    *pathinfile;
    char    *pathoutfile;
}   t_param;

t_param *ft_param(char **argv, char **envp, int i);

void	ft_free_cc(char **split);
void ft_free_param (t_param elem);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:08:08 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/15 13:40:35 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_param
{
	char    *command;
    char    *flags;
    char    *pathname;
	char    *pathinfile;
    char    *pathoutfile;
    char    *path;
    char    *pwd;
}   t_param;

t_param ft_param(char **argv, char **envp, int i);
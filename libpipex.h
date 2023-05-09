/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:08:08 by itovar-n          #+#    #+#             */
/*   Updated: 2023/05/09 15:06:11 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPIPEX_H
# define LIBPIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

char	*ft_envp(char **envp, char *pwd);
char	*ft_find_pwd(char *pwd, char *infile);
char	*ft_find_path(char *path, char *command, char *infile);
char	**ft_flags(char **argv, int i);

void	ft_free_cc(char **split);
void	ft_free_ii(int **split, int i);
void	ft_free_param(char **param);
void	ft_free_cc_c(char **cc, char *c);

int		**ft_pipe(int argc);
void	ft_closepipe(int **p1, int argc);
void	ft_waitpid(int *pid);
void	ft_fork(char **param, int **p1, char **flags, int i);

char	**ft_param(int argc, char **argv, char **envp, int i);

#endif

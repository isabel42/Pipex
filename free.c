/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 13:45:03 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/15 15:17:12 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpipex.h"

void	ft_free_cc(char **split)
{
	int i;
	
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void ft_free_param (t_param *elem)
{
	free(elem->pathname);
	free(elem->pathinfile);
	free(elem->pathoutfile);
}
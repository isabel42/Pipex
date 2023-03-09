/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:06:56 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/08 19:11:10 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen( char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*sol;
	size_t	i;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	sol = malloc((len_s1 + len_s2 + 1) * sizeof(*s1));
	if (!sol)
		return (NULL);
	while (i < len_s1)
	{
		sol[i] = s1[i];
		s1[i] = '\0';
		i++;
	}
	while (i < len_s1 + len_s2)
	{
		sol[i] = s2[i - len_s1];
		i++;
	}
	free(s1);
	sol [i] = '\0';
	return (sol);
}
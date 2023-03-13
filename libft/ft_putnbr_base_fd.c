/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:08:20 by itovar-n          #+#    #+#             */
/*   Updated: 2022/12/20 16:43:20 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_fd(unsigned long long n, char *base, int fd)
{
	unsigned long long	size;	

	size = (unsigned long long) ft_strlen(base);
	if (n < size)
		ft_putchar_fd(base[n], fd);
	else
	{
		ft_putnbr_base_fd(n / size, base, fd);
		ft_putnbr_base_fd(n % size, base, fd);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:08:20 by cbordeau          #+#    #+#             */
/*   Updated: 2024/11/19 10:11:19 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putc(char c, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putc('-', fd);
		nb = nb * (-1);
	}
	if (nb <= 9)
		ft_putc((char)nb + 48, fd);
	if (nb > 9)
	{
		ft_putnbr_fd((int)(nb / 10), fd);
		ft_putnbr_fd((nb % 10), fd);
	}
}

static void	ft_putc(char c, int fd)
{
	write(fd, &c, 1);
}

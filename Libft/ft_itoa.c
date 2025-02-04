/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:27:50 by cbordeau          #+#    #+#             */
/*   Updated: 2024/11/19 10:09:00 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fillnew(char *new, long nb, size_t len);

char	*ft_itoa(int n)
{
	size_t	len;
	long	nb;
	char	*new;

	len = 0;
	nb = n;
	while ((nb / 10) != 0)
	{
		len++;
		nb = nb / 10;
	}
	len++;
	if (n < 0)
		len++;
	new = (char *)malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	nb = n;
	new = ft_fillnew(new, nb, len);
	new[len] = '\0';
	return (new);
}

static char	*ft_fillnew(char *new, long nb, size_t len)
{
	if (nb < 0)
	{
		new[0] = '-';
		nb = nb * (-1);
	}
	if (nb >= 0 && nb <= 9)
	{
		new[len - 1] = (char)nb + 48;
	}
	else if (nb > 9)
	{
		ft_fillnew(new, (nb / 10), (len - 1));
		ft_fillnew(new, (nb % 10), (len));
	}
	return (new);
}

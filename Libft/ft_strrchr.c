/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:49:09 by cbordeau          #+#    #+#             */
/*   Updated: 2024/11/12 16:30:23 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	while (len != 0 && ((char *)s)[len] != (unsigned char)c)
		len--;
	if (((char *)s)[len] == (unsigned char)c)
		return (&((char *)s)[len]);
	return (NULL);
}

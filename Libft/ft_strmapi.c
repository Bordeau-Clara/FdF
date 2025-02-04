/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:16:18 by cbordeau          #+#    #+#             */
/*   Updated: 2024/11/11 16:32:55 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*new;
	size_t	i;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	new = (char *)malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	new[len] = '\0';
	while (i < len)
	{
		new[i] = f((unsigned int)i, s[i]);
		i++;
	}
	return (new);
}

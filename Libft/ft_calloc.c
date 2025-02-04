/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:12:43 by cbordeau          #+#    #+#             */
/*   Updated: 2024/11/12 15:58:25 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new;
	size_t	i;

	if (nmemb == 0 || size == 0)
	{
		new = malloc(0);
		return (new);
	}
	if ((nmemb) > (2147483647 / size))
	{
		new = NULL;
		return (new);
	}
	new = malloc(nmemb * size);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
	{
		((char *)new)[i] = '\0';
		i++;
	}
	return (new);
}

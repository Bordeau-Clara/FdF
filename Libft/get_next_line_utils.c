/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:09:16 by cbordeau          #+#    #+#             */
/*   Updated: 2024/12/04 11:13:35 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_gnl(char *s)
{
	char	*new;
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	new = (char *)malloc((i + 1) * sizeof(char));
	if (new == NULL)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:58:52 by cbordeau          #+#    #+#             */
/*   Updated: 2024/11/12 15:45:46 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_m(const char *s, unsigned int start, size_t len);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	m;

	i = 0;
	m = ft_m(s, start, len);
	new = (char *)malloc((m + 1) * sizeof(char const));
	if (new == NULL)
		return (NULL);
	if (ft_strlen(s) <= start || len == 0)
	{
		new[0] = '\0';
		return (new);
	}
	while (i < (m) && s[start])
	{
		new[i] = s[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}

static size_t	ft_m(const char *s, unsigned int start, size_t len)
{
	size_t	m;
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	if (i < start || len == 0)
		m = 0;
	else if ((i - start) <= len)
		m = i - start;
	else
		m = len;
	return (m);
}

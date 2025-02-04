/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 21:18:29 by cbordeau          #+#    #+#             */
/*   Updated: 2024/11/12 16:00:22 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*new;

	i = 0;
	start = 0;
	end = 0;
	while (ft_isset(s1[start], (char *)set))
		start++;
	while (s1[end])
		end++;
	while (end > start && s1[end - 1] && ft_isset(s1[end - 1], (char *)set))
		end--;
	new = (char *)malloc((end - start + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	while (start + i < end)
	{
		new[i] = s1[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static int	ft_isset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

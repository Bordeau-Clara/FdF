/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:15:10 by cbordeau          #+#    #+#             */
/*   Updated: 2024/11/19 10:11:51 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countwords(char const *s, char c);
static char		**ft_mallocline(char **tab, const char *s, char c);
static char		**ft_filltab(char **tab, const char *s, char c);
static char		**ft_freeall(char **tab, size_t k);

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	count;

	count = ft_countwords(s, c);
	tab = (char **)malloc((count + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab[count] = NULL;
	tab = ft_mallocline(tab, s, c);
	if (tab == NULL)
		return (NULL);
	tab = ft_filltab(tab, s, c);
	return (tab);
}

static size_t	ft_countwords(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
			count++;
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	return (count);
}

static char	**ft_mallocline(char **tab, const char *s, char c)
{
	size_t	i;
	size_t	line;
	size_t	k;

	i = 0;
	k = 0;
	while (k < ft_countwords(s, c))
	{
		line = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			line++;
		}
		tab[k] = (char *)malloc((line + 1) * sizeof(char));
		if (tab[k] == NULL)
			return (ft_freeall(tab, k));
		k++;
	}
	return (tab);
}

static char	**ft_filltab(char **tab, const char *s, char c)
{
	size_t	i;
	size_t	k;
	size_t	j;

	i = 0;
	k = 0;
	while (k < ft_countwords(s, c))
	{
		j = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			tab[k][j] = s[i];
			i++;
			j++;
		}
		tab[k][j] = '\0';
		k++;
	}
	return (tab);
}

static char	**ft_freeall(char **tab, size_t k)
{
	size_t	i;

	i = k;
	while (i > 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab[i]);
	free(tab);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbordeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:01:02 by cbordeau          #+#    #+#             */
/*   Updated: 2024/11/15 11:36:41 by cbordeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_free(t_list **new, void *content, void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*current;
	t_list	*currentnew;
	void	*content;

	if (lst == NULL)
		return (NULL);
	current = lst;
	content = f(current->s);
	new = ft_lstnew(content);
	if (new == NULL)
		return (ft_free(&new, content, del));
	current = current->next;
	while (current != NULL)
	{
		content = f(current->s);
		currentnew = ft_lstnew(content);
		if (currentnew == NULL)
			return (ft_free(&new, content, del));
		ft_lstadd_back(&new, currentnew);
		current = current->next;
	}
	return (new);
}

static void	*ft_free(t_list **new, void *content, void (*del)(void *))
{
	del(content);
	ft_lstclear(new, del);
	return (NULL);
}

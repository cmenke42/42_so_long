/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:44:13 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/18 23:49:33 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_lst	*ft_new_node(int y, int x)
{
	t_lst	*node;

	node = malloc(sizeof(t_lst));
	if (!node)
		return (NULL);
	node->y = y;
	node->x = x;
	node->next = NULL;
	return (node);
}

t_lst	*ft_last_node(t_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_node_add_back(t_lst **lst, t_lst *node)
{
	if (lst)
	{
		if (*lst)
			ft_last_node(*lst)->next = node;
		else
			*lst = node;
	}
}

void	ft_clear_lst(t_lst **lst)
{
	t_lst	*node;

	if (lst)
	{
		while (*lst)
		{
			node = *lst;
			*lst = node->next;
			free(node);
		}
	}
	*lst = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:22:50 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/08 21:04:27 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdlib.h>
#include <stdio.h>

typedef struct s_lst
{
	int				row;
	int				col;
	struct s_lst	*next;
}				t_lst;

//lst_functions
t_lst	*ft_new_node(int row, int col);
t_lst	*ft_last_node(t_lst *lst);
void	ft_node_add_back(t_lst **lst, t_lst *node);
void	ft_clear_lst(t_lst **lst);

#endif
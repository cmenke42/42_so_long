/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:22:50 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/13 21:06:22 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include "../libft/libft.h"
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct s_lst
{
	int				row;
	int				col;
	struct s_lst	*next;
}				t_lst;

typedef struct s_vars
{
	char	*error_text;
	int		exit_code;
	char	**map;
	//height and width are exact
	int		height;
	int		width;
	char	**map_cpy;
	int		player_pos_row;
	int		player_pos_col;
	int		amt_p;
	int		amt_e;
	int		amt_c;
	int		amt_p_e_c;
	int		taken_c;
}				t_vars;

//lst_functions
t_lst	*ft_new_node(int row, int col);
t_lst	*ft_last_node(t_lst *lst);
void	ft_node_add_back(t_lst **lst, t_lst *node);
void	ft_clear_lst(t_lst **lst);

#endif
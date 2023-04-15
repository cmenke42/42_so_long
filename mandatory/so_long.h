/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:22:50 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/15 21:18:34 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include "../libft/libft.h"
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../mlx/mlx.h"

typedef struct s_lst
{
	int				row;
	int				col;
	struct s_lst	*next;
}				t_lst;

enum	e_events
{
	on_keydown = 2,
	win_closed = 17
};

enum	e_keys
{
	key_esc = 53
};

//mlx_ptr is a big struct from mlx
typedef struct s_vars
{
	char	*error_text;
	int		exit_code;
	char	**map;
	char	**map_cpy;
	//height and width are exact
	int		map_hgt;
	int		map_wth;
	int		player_pos_row;
	int		player_pos_col;
	int		amt_p;
	int		amt_e;
	int		amt_c;
	int		amt_p_e_c;
	int		taken_c;
	void	*mlx_ptr;
	void	*win_ptr;
}				t_vars;
typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;


//lst_functions
t_lst	*ft_new_node(int row, int col);
t_lst	*ft_last_node(t_lst *lst);
void	ft_node_add_back(t_lst **lst, t_lst *node);
void	ft_clear_lst(t_lst **lst);

#endif
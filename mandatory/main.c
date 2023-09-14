/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:22:47 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/27 15:28:13 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// 0L 		NoEventMask
// (1L<<0) 	KeyPressMask
// hooks are used to alter the behavior of the mlx
bool	ft_game(t_vars *vars, int win_wth, int win_hgt)
{	
	vars->mlx_ptr = mlx_init();
	if (!vars->mlx_ptr)
		return (ft_error("MLX init failed", 1));
	ft_get_pov_values(vars, &win_wth, &win_hgt);
	vars->win_ptr = mlx_new_window(vars->mlx_ptr, win_wth, win_hgt, "so_long");
	if (!vars->win_ptr)
		return (ft_error("MLX new window failed", 1));
	if (ft_create_mlx_images(vars, IMG_WTH, IMG_HGT) == false)
		return (false);
	mlx_hook(vars->win_ptr, win_closed, 0L, ft_close_window_x, vars);
	mlx_hook(vars->win_ptr, on_keydown, 1L << 0, ft_key_press, vars);
	ft_render_pov(vars, 0, 0);
	mlx_loop(vars->mlx_ptr);
	return (true);
}

bool	ft_check_map(char *map_name, t_vars *vars)
{
	if (ft_check_map_name(map_name) == false)
		return (false);
	if (ft_read_map(map_name, vars) == false)
		return (false);
	if (ft_check_map_chars(vars) == false)
		return (false);
	if (ft_copy_map(vars) == false)
		return (false);
	if (ft_find_path(vars) == false)
	{
		ft_free_map(vars, 1);
		return (false);
	}
	ft_free_map(vars, 1);
	return (true);
}

//y == rows -> top down
//x == collums -> left right
int	main(int argc, char **argv)
{
	t_vars	*vars;

	if (argc != 2)
		exit(ft_error_exit("Wrong ammount of input files", 1));
	vars = malloc(sizeof(t_vars));
	if (!vars)
		exit(ft_error_exit("Malloc error - t_vars node", 1));
	ft_bzero(vars, sizeof(t_vars));
	if (ft_check_map(argv[1], vars) == false)
		vars->exit_code = 1;
	if (vars->exit_code == 0 && ft_game(vars, SCREEN_WTH, SCREEN_HGT) == false)
		vars->exit_code = 1;
	ft_close_game(vars);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:17:10 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/18 23:42:58 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_close_window_esc(int key, t_vars *vars)
{
	if (key == esc)
	{
		ft_close_game(vars);
		return (0);
	}
	return (1);
}

int	ft_close_window_x(t_vars *vars)
{
	ft_close_game(vars);
	return (0);
}

void	ft_free_map(t_vars *vars, int map)
{
	int	y;

	y = 0;
	if (map == 0 && vars->map)
	{
		while (vars->map[y])
			free(vars->map[y++]);
		free(vars->map);
	}
	else if (map == 1 && vars->map_cpy)
	{
		while (vars->map_cpy[y])
			free(vars->map_cpy[y++]);
		free(vars->map_cpy);
	}
}

bool	ft_destroy_mlx_images(t_vars *vars, bool print_error)
{
	if (print_error == true)
	{
		vars->exit_code = 1;
		ft_error("Error creating mlx images", 1);
	}
	if (vars->path_img.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->path_img.img_ptr);
	if (vars->wall_img.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->wall_img.img_ptr);
	if (vars->player_img.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->player_img.img_ptr);
	if (vars->collect_img.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->collect_img.img_ptr);
	if (vars->exit_img.img_ptr)
		mlx_destroy_image(vars->mlx_ptr, vars->exit_img.img_ptr);
	return (false);
}

void	ft_close_game(t_vars *vars)
{
	int	exit_code;

	exit_code = vars->exit_code;
	ft_destroy_mlx_images(vars, false);
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	vars->win_ptr = NULL;
	if (vars->mlx_ptr)
		free(vars->mlx_ptr);
	ft_free_map(vars, 0);
	free(vars);
	exit(exit_code);
}

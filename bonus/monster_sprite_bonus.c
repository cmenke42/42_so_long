/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_sprite_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:22:44 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/24 22:46:10 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

bool	ft_create_mlx_images_monster(t_vars *vars, int wth, int hgt)
{
	vars->exit_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			EXIT_IMG, &wth, &hgt);
	if (!vars->exit_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	vars->exit_two_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			EXIT_TWO_IMG, &wth, &hgt);
	if (!vars->exit_two_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	vars->exit_three_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			EXIT_THREE_IMG, &wth, &hgt);
	if (!vars->exit_three_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	return (true);
}

static void ft_animation(t_vars *vars, void *mlx, void *win, int count)
{
	if (count <= 150)
	{
		mlx_put_image_to_window(mlx, win, vars->exit_img.img_ptr,
			 vars->exit_pos_x * IMG_WTH, vars->exit_pos_y * IMG_HGT);
	}
	else if (count <= 300)
	{
		mlx_put_image_to_window(mlx, win,
				vars->exit_two_img.img_ptr, vars->exit_pos_x * IMG_WTH, vars->exit_pos_y * IMG_HGT);
	}
	else
	{
		mlx_put_image_to_window(mlx, win,
				vars->exit_three_img.img_ptr, vars->exit_pos_x * IMG_WTH, vars->exit_pos_y * IMG_HGT);
	}
}

int	ft_sprite(t_vars *vars)
{
	static int	count;

	if (vars->exit_vis == true)
		ft_animation(vars, vars->mlx_ptr, vars->win_ptr, count);
	if (count++ == 450)
		count = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_sprite_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:22:44 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/27 16:36:09 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

bool	ft_create_mlx_images_monster(t_vars *vars, int wth, int hgt)
{
	vars->monster_img = mlx_xpm_file_to_image(vars->mlx_ptr,
			MONSTER_IMG, &wth, &hgt);
	if (!vars->monster_img)
		return (ft_error("Error creating mlx images", 1));
	vars->monster_two_img = mlx_xpm_file_to_image(vars->mlx_ptr,
			MONSTER_TWO_IMG, &wth, &hgt);
	if (!vars->monster_two_img)
		return (ft_error("Error creating mlx images", 1));
	vars->monster_three_img = mlx_xpm_file_to_image(vars->mlx_ptr,
			MONSTER_THREE_IMG, &wth, &hgt);
	if (!vars->monster_three_img)
		return (ft_error("Error creating mlx images", 1));
	return (true);
}

void	ft_animation(t_vars *vars, int y, int x)
{
	void		*mlx;
	void		*win;

	mlx = vars->mlx_ptr;
	win = vars->win_ptr;
	if (vars->animation_timer <= 25)
		mlx_put_image_to_window(mlx, win, vars->monster_img, x, y);
	else if (vars->animation_timer <= 50)
	{
		mlx_put_image_to_window(mlx, win,
			vars->monster_two_img, x, y);
	}
	else
	{
		mlx_put_image_to_window(mlx, win,
			vars->monster_three_img, x, y);
	}
}

static void	ft_animation_map_check(t_vars *vars, int y_orig, int x_orig)
{
	int	y;
	int	x;
	int	i;
	int	j;

	ft_calculate_pov_offset(vars, &y_orig, &x_orig);
	i = 0;
	y = y_orig;
	while (i < vars->map_hgt && i < vars->pov_u_max + vars->pov_d_max)
	{
		j = 0;
		x = x_orig;
		while (j < vars->map_wth && j < vars->pov_l_max + vars->pov_r_max)
		{
			if (vars->map[y][x] == 'M')
				ft_animation(vars, i * IMG_HGT, j * IMG_WTH);
			j++;
			x++;
		}
		i++;
		y++;
	}
}

int	ft_monster_animation(t_vars *vars)
{
	if (vars->animation_timer++ >= 75)
		vars->animation_timer = 0;
	ft_animation_map_check(vars, 0, 0);
	return (0);
}

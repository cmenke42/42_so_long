/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_sprite_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 02:22:44 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/19 03:08:11 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

bool	ft_create_mlx_images_monster(t_vars *vars, int wth, int hgt)
{
	vars->monster_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			MONSTER_IMG, &wth, &hgt);
	if (!vars->monster_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	vars->monster_two_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			MONSTER_TWO_IMG, &wth, &hgt);
	if (!vars->monster_two_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	vars->monster_three_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			MONSTER_THREE_IMG, &wth, &hgt);
	if (!vars->monster_three_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	return (true);
}

static void	ft_sprite(t_vars *vars, char c, int y, int x)
{
	void		*mlx;
	void		*win;
	static int	count;

	mlx = vars->mlx_ptr;
	win = vars->win_ptr;
	if (c == 'M')
	{
		if (count <= 150000)
			mlx_put_image_to_window(mlx, win, vars->monster_img.img_ptr, x, y);
		else if (count <= 300000)
		{
			mlx_put_image_to_window(mlx, win,
					vars->monster_two_img.img_ptr, x, y);
		}
		else
		{
			mlx_put_image_to_window(mlx, win,
					vars->monster_three_img.img_ptr, x, y);
		}
	}
	if (count++ == 450000)
		count = 0;
}

int	ft_monster_sprite(t_vars *vars)
{
	int	y;
	int	x;
	int	i;
	int	j;

	i = 0;
	if (vars->pov_u != 0 && vars->p_pos_y - vars->pov_u >= 0)
		y = vars->p_pos_y - vars->pov_u;
	else
		y = 0;
	while (y >= 0 && y < vars->map_hgt && i < vars->pov_u_max + vars->pov_d_max)
	{
		if (vars->pov_l != 0 && vars->p_pos_x - vars->pov_l >= 0)
			x = vars->p_pos_x - vars->pov_l;
		else
			x = 0;
		j = 0;
		while (x >= 0 && x < vars->map_wth
			&& j < vars->pov_l_max + vars->pov_r_max)
		{
			ft_sprite(vars, vars->map[y][x++], i * IMG_HGT, j++ * IMG_WTH);
		}
		i++;
		y++;
	}
	return (0);
}
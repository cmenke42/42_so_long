/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map_on_screen_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:22:22 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/19 02:40:39 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

//added a line for monster
bool	ft_create_mlx_images(t_vars *vars, int wth, int hgt)
{
	vars->path_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			PATH_IMG, &wth, &hgt);
	if (!vars->path_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	vars->wall_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			WALL_IMG, &wth, &hgt);
	if (!vars->wall_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	vars->player_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			PLAYER_IMG, &wth, &hgt);
	if (!vars->player_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	vars->collect_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			COLLECT_IMG, &wth, &hgt);
	if (!vars->collect_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	vars->exit_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr,
			EXIT_IMG, &wth, &hgt);
	if (!vars->exit_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	if (ft_create_mlx_images_monster(vars, wth, hgt) == false)
		return (false);
	return (true);
}

//added a line for monster
static void	ft_put_images_on_map(t_vars *vars, char c, int i, int j)
{
	int		x;
	int		y;
	void	*mlx;
	void	*win;

	y = i * IMG_HGT;
	x = j * IMG_WTH;
	mlx = vars->mlx_ptr;
	win = vars->win_ptr;
	if (c == '0')
		mlx_put_image_to_window(mlx, win, vars->path_img.img_ptr, x, y);
	else if (c == '1')
		mlx_put_image_to_window(mlx, win, vars->wall_img.img_ptr, x, y);
	else if (c == 'C')
		mlx_put_image_to_window(mlx, win, vars->collect_img.img_ptr, x, y);
	else if (c == 'E')
		mlx_put_image_to_window(mlx, win, vars->exit_img.img_ptr, x, y);
	else if (c == 'P')
		mlx_put_image_to_window(mlx, win, vars->player_img.img_ptr, x, y);
}

int	ft_render_pov(t_vars *vars)
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
			ft_put_images_on_map(vars, vars->map[y][x++], i, j++);
		i++;
		y++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map_on_screen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:22:22 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/27 16:37:04 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	ft_create_mlx_images(t_vars *vars, int wth, int hgt)
{
	vars->path_img = mlx_xpm_file_to_image(vars->mlx_ptr,
			PATH_IMG, &wth, &hgt);
	if (!vars->path_img)
		return (ft_error("Error creating mlx images", 1));
	vars->wall_img = mlx_xpm_file_to_image(vars->mlx_ptr,
			WALL_IMG, &wth, &hgt);
	if (!vars->wall_img)
		return (ft_error("Error creating mlx images", 1));
	vars->player_img = mlx_xpm_file_to_image(vars->mlx_ptr,
			PLAYER_IMG, &wth, &hgt);
	if (!vars->player_img)
		return (ft_error("Error creating mlx images", 1));
	vars->collect_img = mlx_xpm_file_to_image(vars->mlx_ptr,
			COLLECT_IMG, &wth, &hgt);
	if (!vars->collect_img)
		return (ft_error("Error creating mlx images", 1));
	vars->exit_img = mlx_xpm_file_to_image(vars->mlx_ptr,
			EXIT_IMG, &wth, &hgt);
	if (!vars->exit_img)
		return (ft_error("Error creating mlx images", 1));
	return (true);
}

static void	ft_put_imgage(t_vars *vars, char c, int y, int x)
{
	void	*mlx;
	void	*win;

	mlx = vars->mlx_ptr;
	win = vars->win_ptr;
	if (c == '0')
		mlx_put_image_to_window(mlx, win, vars->path_img, x, y);
	else if (c == '1')
		mlx_put_image_to_window(mlx, win, vars->wall_img, x, y);
	else if (c == 'C')
		mlx_put_image_to_window(mlx, win, vars->collect_img, x, y);
	else if (c == 'E')
		mlx_put_image_to_window(mlx, win, vars->exit_img, x, y);
	else if (c == 'P')
		mlx_put_image_to_window(mlx, win, vars->player_img, x, y);
}

void	ft_calculate_pov_offset(t_vars *vars, int *y, int *x)
{
	if (vars->pov_u != 0 && vars->p_pos_y - vars->pov_u >= 0)
		*y = vars->p_pos_y - vars->pov_u;
	else
		*y = 0;
	if (vars->pov_l != 0 && vars->p_pos_x - vars->pov_l >= 0)
			*x = vars->p_pos_x - vars->pov_l;
	else
			*x = 0;
}

int	ft_render_pov(t_vars *vars, int y_orig, int x_orig)
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
			ft_put_imgage(vars, vars->map[y][x], i * IMG_HGT, j * IMG_WTH);
			j++;
			x++;
		}
		i++;
		y++;
	}
	return (0);
}

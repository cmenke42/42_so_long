/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:22:47 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/18 19:14:02 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

///
//mlx things
///

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

/// @brief -> creates an TRGB int value, each value goes from  0 to 255.
// 				each parameter is one byte (8 bits) big
/// @param t transparency 
/// @param r red 
/// @param g green
/// @param b blue
int	ft_create_color(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

//mit offset starten. 1920 / 30 und 1080 / 30 als Sichtfeld.
//Checken ob außenkante erreicht wurde primär und secundär die sichtfeldgröße als Maße
//so bewegen dass p_pos_x - offset <= pov_left und right max
int	ft_render_pov(t_vars *vars)
{
	int	y;
	int	x;
	int	i;
	int	j;

	if (!vars->win_ptr)
		return (1);
	j = 0;
	if (vars->pov_u != 0 && vars->p_pos_y - vars->pov_u >= 0)
		y = vars->p_pos_y - vars->pov_u;
	else
		y = 0;
	while(y >= 0 && y < vars->map_hgt && j < vars->pov_u_max + vars->pov_d_max)
	{
		if (vars->pov_l != 0 && vars->p_pos_x - vars->pov_l >= 0)
			x = vars->p_pos_x - vars->pov_l;
		else
			x = 0;
		i = 0;
		while (x >= 0 && x < vars->map_wth && i < vars->pov_l_max + vars->pov_r_max)
		{
			if (vars->map[y][x] == '0')
				mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->path_img.img_ptr, i * IMG_WTH, j * IMG_HGT);
			else if (vars->map[y][x] == '1')
				mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->wall_img.img_ptr, i * IMG_WTH, j * IMG_HGT);
			else if (vars->map[y][x] == 'C')
				mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->collect_img.img_ptr, i * IMG_WTH, j * IMG_HGT);
			else if (vars->map[y][x] == 'E')
				mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->exit_img.img_ptr, i * IMG_WTH, j * IMG_HGT);
			else if (vars->map[y][x] == 'P')
				mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->player_img.img_ptr, i * IMG_WTH, j * IMG_HGT);
			x++;
			i++;
		}
		j++;
		y++;
	}
	return (0);
}

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
	return (true);
}

void	ft_swap(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

//make sure the exit doesnt change position if you nove over it
bool	ft_check_move(t_vars *vars, char *c)
{
	if (*c == '0')
		return (true);
	else if (*c == 'C')
	{
		vars->taken_c++;
		*c = '0';
	}
	else if (*c == 'E')
	{
		if (vars->taken_c == vars->amt_c)
			ft_close_game(vars);
		else
			*c = '0';
	}
	else
		return (false);
	return (true);
}

bool	ft_move_p(t_vars *vars, int y, int x)
{
	if (ft_check_move(vars, &vars->map[y][x]) == false)
		return (false);
	ft_printf("MOVE: %d\n", ++(vars->num_moves));
	ft_swap(&vars->map[vars->p_pos_y][vars->p_pos_x], &vars->map[y][x]);
	if (vars->exit_pos_y == vars->p_pos_y && vars->exit_pos_x == vars->p_pos_x)
		vars->map[vars->exit_pos_y][vars->exit_pos_x] = 'E';
	vars->p_pos_y = y;
	vars->p_pos_x = x;
	// ft_render(vars);
	return (true);
}

//starts moving the map instant till you can see the end of the map
void	ft_change_pov_values_on_move(t_vars *vars, int y, int x)
{
	//vars->pov_r < vars->pov_r_max || vars->pov_l < vars->pov_l_max || -> add this to only move screen when crossing center and stay near center
	if (x != 0 && vars->pov_l_max + vars->pov_r_max < vars->map_wth)
	{
		if ((vars->pov_r < vars->pov_r_max || vars->pov_l < vars->pov_l_max
			|| vars->p_pos_x + vars->pov_r > vars->map_wth
			|| vars->p_pos_x - vars->pov_l < 0) && vars->pov_l + x >= 0)
		{
			vars->pov_l += x;
			vars->pov_r = vars->pov_r_max + (vars->pov_l_max - vars->pov_l);
		}
	}
	//vars->pov_u < vars->pov_u_max || vars->pov_d < vars->pov_d_max || -> add this to only move screen when crossing center and stay near center
	if (y != 0 && vars->pov_u_max + vars->pov_d_max < vars->map_hgt)
	{
		if ((vars->pov_u < vars->pov_u_max || vars->pov_d < vars->pov_d_max
			|| vars->p_pos_y + vars->pov_d > vars->map_hgt
			|| vars->p_pos_y - vars->pov_u < 0) && vars->pov_u + y >= 0)
		{
			vars->pov_u += y;
			vars->pov_d = vars->pov_d_max + (vars->pov_u_max - vars->pov_u);
		}
	}
	ft_printf("%d %d %d %d\n", vars->pov_u, vars->pov_d, vars->pov_l, vars->pov_r);
}

int	ft_key_press(int key, t_vars *vars)
{
	if (key == arrow_u && ft_move_p(vars, vars->p_pos_y - 1, vars->p_pos_x))
		ft_change_pov_values_on_move(vars, -1, 0);
	else if (key == arrow_d && ft_move_p(vars, vars->p_pos_y + 1, vars->p_pos_x))
		ft_change_pov_values_on_move(vars, 1, 0);
	else if (key == arrow_l && ft_move_p(vars, vars->p_pos_y, vars->p_pos_x - 1))
		ft_change_pov_values_on_move(vars, 0, -1);
	else if (key == arrow_r && ft_move_p(vars, vars->p_pos_y, vars->p_pos_x + 1))
		ft_change_pov_values_on_move(vars, 0, 1);
	else if (key == esc)
		ft_close_game(vars);
	else
		return (1);
	ft_render_pov(vars);
	return (0);
}

void	ft_get_pov_range_y(t_vars *vars)
{
	if (vars->p_pos_y < vars->pov_u_max)
	{
		vars->pov_u = vars->p_pos_y;
		vars->pov_d = vars->pov_d_max + vars->pov_u_max - vars->pov_u;
	}
	else if (vars->map_hgt - vars->p_pos_y < vars->pov_d_max)
	{
		vars->pov_d = vars->map_hgt - vars->p_pos_y;
		vars->pov_u = vars->pov_d_max + vars->pov_u_max - vars->pov_d;
	}
	else
	{
		vars->pov_u = vars->pov_u_max;
		vars->pov_d = vars->pov_d_max;
	}
}

void	ft_get_pov_range_x(t_vars *vars)
{
	if (vars->p_pos_x < vars->pov_l_max)
	{
		vars->pov_l = vars->p_pos_x;
		vars->pov_r = vars->pov_r_max + vars->pov_l_max - vars->pov_l;
	}
	else if (vars->map_wth - vars->p_pos_x < vars->pov_r_max)
	{
		vars->pov_r = vars->map_wth - vars->p_pos_x;
		vars->pov_l = vars->pov_r_max + vars->pov_l_max - vars->pov_r;
	}
	else
	{
		vars->pov_l = vars->pov_l_max;
		vars->pov_r = vars->pov_r_max;
	}
}

//calculate pov values and window size
void	ft_get_pov_values(t_vars *vars, int *win_wth, int *win_hgt)
{
	if (vars->map_hgt * IMG_HGT < SCREEN_HGT - IMG_HGT)
	{
		*win_hgt = vars->map_hgt * IMG_HGT;
		vars->pov_u_max = vars->map_hgt;
	}
	else
		vars->pov_u_max = (*win_hgt / IMG_HGT) / 2;
	if (vars->map_wth * IMG_WTH < SCREEN_WTH - IMG_WTH)
	{
		*win_wth = vars->map_wth * IMG_WTH;
		vars->pov_l_max = vars->map_wth;
	}
	else
		vars->pov_l_max = (*win_wth / IMG_WTH) / 2;
	vars->pov_d_max = vars->pov_u_max;
	vars->pov_r_max = vars->pov_l_max;
	if (vars->pov_u_max + vars->pov_d_max < vars->map_hgt)
		ft_get_pov_range_y(vars);
	if (vars->pov_l_max + vars->pov_r_max < vars->map_wth)
		ft_get_pov_range_x(vars);
	ft_printf("%d %d %d %d\n", vars->pov_u_max, vars->pov_d_max, vars->pov_l_max, vars->pov_r_max);
	ft_printf("top:%d bot:%d left:%d right:%d\n", vars->pov_u, vars->pov_d, vars->pov_l, vars->pov_r);
}

bool	ft_game(t_vars *vars)
{	
	int	win_wth;
	int	win_hgt;

	win_hgt = SCREEN_HGT;
	win_wth = SCREEN_WTH;
	vars->mlx_ptr = mlx_init();
	if (!vars->mlx_ptr)
		return (ft_error("MLX init failed", 1));
	ft_get_pov_values(vars, &win_wth, &win_hgt);
	vars->win_ptr = mlx_new_window(vars->mlx_ptr, win_wth, win_hgt, "so_long");
	if (!vars->mlx_ptr)
	{
		free(vars->mlx_ptr);
		return (ft_error("MLX init failed", 1));
	}
	if (ft_create_mlx_images(vars, IMG_WTH, IMG_HGT) == false)
		return (false);
	mlx_hook(vars->win_ptr, win_closed, 0L, ft_close_window_x, vars);
	mlx_hook(vars->win_ptr, on_keydown, 1L<<0, ft_key_press, vars);
	ft_render_pov(vars);
	// ft_render(vars);
	// mlx_loop_hook(vars->mlx_ptr, ft_render, vars);
	mlx_loop(vars->mlx_ptr);
	return (true);
}

//y == rows -> top down
//x == collums -> left right
int	main(int argc, char **argv)
{
	t_vars *vars;
	int		exit_code;
	

	exit_code = 0;
	if (argc != 2)
		return (ft_error_exit("Wrong input file", 1));
	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (ft_error_exit("Malloc error", 1));
	ft_bzero(vars, sizeof(t_vars));
	if (ft_check_map(argv[1], vars) == false)
		exit_code = 1;
	if (exit_code == 0 && ft_game(vars) == false)
		exit_code = 1;
	if (exit_code == 0)
		ft_printf("\n\n##all good##\n\n");
	//close game???
	ft_free_map(vars, 0);
	free (vars);
	return (exit_code);
}
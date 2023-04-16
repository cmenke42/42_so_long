/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:22:47 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/16 21:47:13 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	ft_error_exit(char	*error_text, int exit_code)
{
		write(2, "Error\n", 6);
		ft_putendl_fd(error_text, 2);
		ft_putendl_fd("\n", 2);
		return (exit_code);
}

bool	ft_error(char	*error_text, int exit_code)
{
	if (exit_code != 0)
	{
		write(2, "Error\n", 6);
		ft_putendl_fd(error_text, 2);
		ft_putendl_fd("\n", 2);
		return (false);
		// exit(exit_code);
	}
	return (true);
}

bool	ft_check_map_name(char *map_name)
{
	int	name_len;

	name_len = ft_strlen(map_name);
	if (name_len > 4)
	{
		if (ft_strncmp(map_name + (name_len - 4), ".ber", 4) == 0)
			return (true);
	}
	return (ft_error("Wrong map Name", 1));
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

bool	ft_add_line(char *line_read, t_vars *vars)
{
	char	**map_new;
	int		y;

	vars->map_hgt++;
	if (vars->map_hgt == 1)
		vars->map_wth = ft_strlen(line_read) - 1;
	map_new = (char **)malloc((vars->map_hgt + 1) * sizeof(char *));
	if (!map_new)
		return (ft_error("Malloc error", 1));
	y = -1;
	while (++y < vars->map_hgt - 1)
		map_new[y] = vars->map[y];
	map_new[y++] = line_read;
	map_new[y] = NULL;
	if (vars->map)
		free(vars->map);
	vars->map = map_new;
	return (true);
}

bool ft_read_map(char *map_name, t_vars *vars)
{
	int		fd;
	char	*line_read;
	
	fd = open(map_name, O_RDONLY);
	if (fd <= -1)
		return (ft_error("Error opening the file", 1));
	line_read = get_next_line(fd);
	while (line_read)
	{
		if (ft_add_line(line_read, vars) == true)
			line_read = get_next_line(fd);
		else
		{
			if (line_read)
				free(line_read);
			line_read = get_next_line(-1);
			return (false);
		}
	}
	close(fd);
	return (true);
}

bool	ft_valid_char(char c, t_vars *vars, int y, int x)
{
	if (c == '0' || c == '1')
		return (true);
	else if (c == 'C')
		vars->amt_c++;
	else if(c == 'E' )
	{
		vars->exit_pos_y = y;
		vars->exit_pos_x = x;
		vars->amt_e++;
		if (vars->amt_e != 1)
			return (ft_error("Too many of E", 1));
	}
	else if (c == 'P')
	{
		vars->player_pos_y = y;
		vars->player_pos_x= x;
		vars->amt_p++;
		if (vars->amt_p != 1)
			return (ft_error("Too many of P", 1));
	}
	else
		return (ft_error("Invalid chars", 1));
	return (true);
}

bool	ft_check_map_lines(t_vars *vars, int y, int x)
{
	while (vars->map[y])
	{
		x = 0;
		if (vars->map[y][x++] != '1')
				return (ft_error("Not surrounded by '1'", 1));
		while (vars->map[y][x] && vars->map[y][x] != '\n')
		{
			if (x == 0 || y + 1 == vars->map_hgt)
			{
				if (vars->map[y][x] != '1')
					return (ft_error("Not surrounded by '1'", 1));
			}
			else if (ft_valid_char(vars->map[y][x], vars, y, x) == false)
				return (false);
			x++;
		}
		if (x != vars->map_wth)
			return (ft_error("Not a rectangle", 1));
		if (vars->map[y][x - 1] != '1')
			return (ft_error("Not surrounded by '1'", 1));
		y++;
	}
	return (true);
}

bool	ft_check_map_chars(t_vars *vars)
{
	if (vars->map_wth < 3 || vars->map_hgt < 3)
		return (ft_error("Map too small", 1));
	if (ft_check_map_lines(vars, 0, 0) == false)
		return (false);
	if (vars->amt_e != 1 || vars->amt_p != 1 || vars->amt_c < 1)
		return (ft_error("Wrong ammount of E P or C", 1));
	return (true);
}

bool	ft_copy_map(t_vars *vars)
{
	int		y;
	
	vars->map_cpy = (char **)malloc((vars->map_hgt + 1) * sizeof(char *));
	if (!vars->map_cpy)
		return (ft_error("Malloc error", 1));
	y = 0;
	while (vars->map[y])
	{
		vars->map_cpy[y] = ft_strdup(vars->map[y]);
		if (!vars->map_cpy[y])
		{
			ft_free_map(vars, 1);
			return (ft_error("Malloc error", 1));
		}
		y++;
	}
	vars->map_cpy[y] = NULL;
	return (true);
}

bool	ft_check_field(char c, t_vars *vars)
{
	if (c == '0')
		return (true);
	else if (c == '1')
		return (false);
	else if (c == 'C' || c == 'E' || c == 'P')
		vars->amt_p_e_c++;
	else
		return (false);
	return (true);
}
bool	ft_do_direction(t_vars *vars, t_lst **pos_stk, int y, int x)
{
	t_lst *temp;
	
	if (ft_check_field(vars->map_cpy[y][x], vars))
	{
		vars->map_cpy[y][x] = '1';
		temp = ft_new_node(y, x);
		if (!temp)
		{
			ft_clear_lst(pos_stk);
			return (ft_error("Malloc error", 1));
		}
		ft_node_add_back(pos_stk, temp);
	}
	return (true);
}

bool	ft_check_dir(t_vars *vars, int y, int x, t_lst **pos_stk)
{
	if (!(y < 0 || y >= vars->map_hgt || x < 0 || x >= vars->map_wth))
	{
		if (ft_do_direction(vars, pos_stk, y + 1, x) == false)
			return (false);
		if (ft_do_direction(vars, pos_stk, y - 1, x) == false)
			return (false);
		if (ft_do_direction(vars, pos_stk, y, x + 1) == false)
			return (false);
		if (ft_do_direction(vars, pos_stk, y, x - 1) == false)
			return (false);
	}
	return (true);
}

bool	ft_find_path(t_vars *vars)
{
	t_lst	*pos_stk;
	t_lst	*temp;
	
	pos_stk = ft_new_node(vars->player_pos_y, vars->player_pos_x);
	if (!pos_stk)
		return (ft_error("Malloc error", 1));
	while (pos_stk)
	{
		if (ft_check_dir(vars, pos_stk->y, pos_stk->x, &pos_stk) == false)
			return (false);
		temp = pos_stk;
		pos_stk = pos_stk->next;
		free(temp);
	}
	ft_clear_lst(&pos_stk);
	if (vars->amt_p + vars->amt_e + vars->amt_c != vars->amt_p_e_c)
		return (ft_error("No valid path", 1));
	return (true);
}

bool	ft_check_path(t_vars *vars)
{
	if (ft_copy_map(vars) == false)
		return (false);
	if (ft_find_path(vars) == false)
	{
		ft_free_map(vars, 1);
		return (false);
	}
	// int i = 0;
	// while (vars->map_cpy[i])
	// 	ft_printf("%s", vars->map_cpy[i++]);
	ft_free_map(vars, 1);
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
	if (ft_check_path(vars) == false)
		return (false);
	return (true);
}

/////
//above all for error and map checking
////

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

int	ft_close_window_esc(int keycode, t_vars *vars)
{
	if (keycode == key_esc)
	{
		ft_close_game(vars);
		// mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		return (0);
	}
	return (1);
}

int	ft_close_window_x(t_vars *vars)
{
	// mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	ft_close_game(vars);
	return (0);
}

/// @brief -> creates an TRGB int value, each value goes from  0 to 255.
// 				each parameter is one byte (8 bits) big
/// @param t transparency 
/// @param r red 
/// @param g green
/// @param b blue
int	ft_create_xor(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

//mit offset starten. 1920 / 30 und 1080 / 30 als Sichtfeld.
//Checken ob außenkante erreicht wurde primär und secundär die sichtfeldgröße als Maße
int	ft_render(t_vars *vars)
{
	int	y;
	int	x;

	if (!vars->win_ptr)
		return (1);
	y = 0;
	while(y < vars->map_hgt)
	{
		x = 0;
		while (x < vars->map_wth)
		{
			if (vars->map[y][x] == '0')
				mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->path_img.img_ptr, x * IMG_WTH, y * IMG_HGT);
			else if (vars->map[y][x] == '1')
				mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->wall_img.img_ptr, x * IMG_WTH, y * IMG_HGT);
			else if (vars->map[y][x] == 'C')
				mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->collect_img.img_ptr, x * IMG_WTH, y * IMG_HGT);
			else if (vars->map[y][x] == 'E')
				mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->exit_img.img_ptr, x * IMG_WTH, y * IMG_HGT);
			else if (vars->map[y][x] == 'P')
				mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->player_img.img_ptr, x * IMG_WTH, y * IMG_HGT);
			x++;
		}
		y++;
	}
	// mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->path_img.img_ptr, vars->player_pos_x * 30, vars->player_pos_y * 30);
	return (0);
}

bool	ft_create_mlx_images(t_vars *vars)
{
	int	wth;
	int	hgt;

	wth = IMG_WTH;
	hgt = IMG_HGT;
	
	//free the rest if one lower gets failed
	vars->path_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr, PATH_IMG, &wth, &hgt);
	if (!vars->path_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	vars->wall_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr, WALL_IMG, &wth, &hgt);
	if (!vars->wall_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	vars->player_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr, PLAYER_IMG, &wth, &hgt);
	if (!vars->player_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	vars->collect_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr, COLLECT_IMG, &wth, &hgt);
	if (!vars->collect_img.img_ptr)
		return (ft_destroy_mlx_images(vars, true));
	vars->exit_img.img_ptr = mlx_xpm_file_to_image(vars->mlx_ptr, EXIT_IMG, &wth, &hgt);
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
bool	ft_check_move(t_vars *vars, int y, int x)
{
	char c;

	c = vars->map[y][x];
	// ft_printf("CHAR: %c\n", c);
	// ft_printf("y: %d\n", y);
	// ft_printf("x: %d\n", x);
	if (c == '0')
		return (true);
	else if (c == 'C')
	{
		vars->taken_c++;
		vars->map[y][x] = '0';
	}
	else if (c == 'E')
	{
		if (vars->taken_c == vars->amt_c)
			ft_close_game(vars);
		else if (vars->exit_pos_y == y && vars->exit_pos_x == x)
			vars->map[y][x] = '0';
	}
	else
		return (false);
	return (true);
}

void	ft_change_player_pos(t_vars *vars, int y, int x)
{
	if (ft_check_move(vars, y, x) == false)
		return ;
	ft_printf("MOVE: %d\n", ++(vars->num_moves));
	ft_swap(&vars->map[vars->player_pos_y][vars->player_pos_x], &vars->map[y][x]);
	if (vars->exit_pos_y == vars->player_pos_y && vars->exit_pos_x == vars->player_pos_x)
		vars->map[vars->exit_pos_y][vars->exit_pos_x] = 'E';
	vars->player_pos_y = y;
	vars->player_pos_x = x;
}

int	ft_key_press(int keycode, t_vars *vars)
{
	if (keycode == arrow_left)
		ft_change_player_pos(vars, vars->player_pos_y, vars->player_pos_x - 1);
	else if (keycode == arrow_right)
		ft_change_player_pos(vars, vars->player_pos_y, vars->player_pos_x + 1);
	else if (keycode == arrow_up)
		ft_change_player_pos(vars, vars->player_pos_y - 1, vars->player_pos_x);
	else if (keycode == arrow_down)
		ft_change_player_pos(vars, vars->player_pos_y + 1, vars->player_pos_x);
	else if (keycode == key_esc)
		ft_close_game(vars);
	else
		return (1);
	return (0);
}

bool	ft_game(t_vars *vars)
{	
	vars->mlx_ptr = mlx_init();
	if (!vars->mlx_ptr)
		return (ft_error("MLX init failed", 1));
	vars->win_ptr = mlx_new_window(vars->mlx_ptr, SCREEN_WTH, SCREEN_HGT, "so_long");
	if (!vars->mlx_ptr)
	{
		free(vars->mlx_ptr);
		return (ft_error("MLX init failed", 1));
	}
	if (ft_create_mlx_images(vars) == false)
		return (false);
	mlx_hook(vars->win_ptr, win_closed, 0L, ft_close_window_x, vars);
	mlx_hook(vars->win_ptr, on_keydown, 1L<<0, ft_key_press, vars);
	mlx_loop_hook(vars->mlx_ptr, ft_render, vars);
	mlx_loop(vars->mlx_ptr);
	return (true);
}


//y == ys -> top down
//x == xums -> left right
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
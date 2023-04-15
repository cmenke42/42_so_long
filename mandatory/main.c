/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:22:47 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/15 20:15:26 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	ft_error_exit(char	*error_text, int exit_code)
{
		ft_printf("Error\n");
		ft_printf("%s\n", error_text);
		return (exit_code);
}

bool	ft_error(char	*error_text, int exit_code)
{
	if (exit_code != 0)
	{
		ft_printf("Error\n");
		ft_printf("%s\n", error_text);
		return (false);
		// exit(exit_code);
	}
	return (true);
}

bool	ft_check_map_name(char *map_name, t_vars *vars)
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
	int	i;

	i = 0;
	if (map == 0 && vars->map)
	{
		while (vars->map[i])
			free(vars->map[i++]);
		free(vars->map);
	}
	else if (map == 1 && vars->map_cpy)
	{
		while (vars->map_cpy[i])
			free(vars->map_cpy[i++]);
		free(vars->map_cpy);
	}
}

bool	ft_add_line(char *line_read, t_vars *vars)
{
	char	**map_new;
	int		i;

	vars->map_hgt++;
	if (vars->map_hgt == 1)
		vars->map_wth = ft_strlen(line_read) - 1;
	map_new = (char **)malloc((vars->map_hgt + 1) * sizeof(char *));
	if (!map_new)
		return (ft_error("Malloc error", 1));
	i = -1;
	while (++i < vars->map_hgt - 1)
		map_new[i] = vars->map[i];
	map_new[i++] = line_read;
	map_new[i] = NULL;
	if (vars->map)
		free(vars->map);
	vars->map = map_new;
	return (true);
}

bool ft_read_map(char *map_name, t_vars *vars)
{
	int		fd;
	bool	result;
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

bool	ft_valid_char(char c, t_vars *vars, int row, int col)
{
	if (c == '0' || c == '1')
		return (true);
	else if (c == 'C')
		vars->amt_c++;
	else if(c == 'E' )
	{
		vars->amt_e++;
		if (vars->amt_e != 1)
			return (ft_error("Too many of E", 1));
	}
	else if (c == 'P')
	{
		vars->player_pos_row = row;
		vars->player_pos_col= col;
		vars->amt_p++;
		if (vars->amt_p != 1)
			return (ft_error("Too many of P", 1));
	}
	else
		return (ft_error("Invalid chars", 1));
	return (true);
}

bool	ft_check_map_lines(t_vars *vars, int i, int j)
{
	while (vars->map[i])
	{
		j = 0;
		if (vars->map[i][j++] != '1')
				return (ft_error("Not surrounded by '1'", 1));
		while (vars->map[i][j] && vars->map[i][j] != '\n')
		{
			if (i == 0 || i + 1 == vars->map_hgt)
			{
				if (vars->map[i][j] != '1')
					return (ft_error("Not surrounded by '1'", 1));
			}
			else if (ft_valid_char(vars->map[i][j], vars, i, j) == false)
				return (false);
			j++;
		}
		if (j != vars->map_wth)
			return (ft_error("Not a rectangle", 1));
		if (vars->map[i][j - 1] != '1')
			return (ft_error("Not surrounded by '1'", 1));
		i++;
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
	int		i;
	
	vars->map_cpy = (char **)malloc((vars->map_hgt + 1) * sizeof(char *));
	if (!vars->map_cpy)
		return (ft_error("Malloc error", 1));
	i = 0;
	while (vars->map[i])
	{
		vars->map_cpy[i] = ft_strdup(vars->map[i]);
		if (!vars->map_cpy[i])
		{
			ft_free_map(vars, 1);
			return (ft_error("Malloc error", 1));
		}
		i++;
	}
	vars->map_cpy[i] = NULL;
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
bool	ft_do_direction(t_vars *vars, t_lst **pos_stk, int row, int col)
{
	t_lst *temp;
	
	if (ft_check_field(vars->map_cpy[row][col], vars))
	{
		vars->map_cpy[row][col] = '1';
		temp = ft_new_node(row, col);
		if (!temp)
		{
			ft_clear_lst(pos_stk);
			return (ft_error("Malloc error", 1));
		}
		ft_node_add_back(pos_stk, temp);
	}
	return (true);
}

bool	ft_check_dir(t_vars *vars, int row, int col, t_lst **pos_stk)
{
	if (!(row < 0 || row >= vars->map_hgt || col < 0 || col >= vars->map_wth))
	{
		if (ft_do_direction(vars, pos_stk, row + 1, col) == false)
			return (false);
		if (ft_do_direction(vars, pos_stk, row - 1, col) == false)
			return (false);
		if (ft_do_direction(vars, pos_stk, row, col + 1) == false)
			return (false);
		if (ft_do_direction(vars, pos_stk, row, col - 1) == false)
			return (false);
	}
	return (true);
}

bool	ft_find_path(t_vars *vars)
{
	t_lst	*pos_stk;
	t_lst	*temp;
	
	pos_stk = ft_new_node(vars->player_pos_row, vars->player_pos_col);
	if (!pos_stk)
		return (ft_error("Malloc error", 1));
	while (pos_stk)
	{
		if (ft_check_dir(vars, pos_stk->row, pos_stk->col, &pos_stk) == false)
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
	if (ft_check_map_name(map_name, vars) == false)
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

bool	ft_game(t_vars *vars)
{	
	vars->mlx_ptr = mlx_init();
	if (!vars->mlx_ptr)
		return (ft_error("MLX init failed", 1));
	vars->win_ptr = mlx_new_window(vars->mlx_ptr, 1920, 1080, "so_long");
	if (!vars->mlx_ptr)
	{
		free(vars->mlx_ptr);
		return (ft_error("MLX init failed", 1));
	}
	mlx_loop(vars->mlx_ptr);
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	free(vars->mlx_ptr);
	return (true);
}


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
	if (ft_game(vars) == false)
		exit_code = 1;
	if (exit_code == 0)
		ft_printf("\n\n##all good##\n\n");
	//close game???
	ft_free_map(vars, 0);
	free (vars);
	return (exit_code);
}
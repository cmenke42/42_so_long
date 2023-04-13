/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:22:47 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/13 20:28:57 by user             ###   ########.fr       */
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

void	ft_free_map(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->map)
	{
		while (vars->map[i])
			free(vars->map[i++]);
		free(vars->map);
	}
}

bool	ft_add_line(char *line_read, t_vars *vars)
{
	char	**map_new;
	int		i;

	vars->height++;
	if (vars->height == 1)
		vars->width = ft_strlen(line_read) - 1;
	map_new = (char **)malloc((vars->height + 1) * sizeof(char *));
	if (!map_new)
		return (ft_error("Malloc error", 1));
	i = -1;
	while (++i < vars->height - 1)
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

bool	ft_valid_char(char c, t_vars *vars)
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
			if (i == 0 || i + 1 == vars->height)
			{
				if (vars->map[i][j] != '1')
					return (ft_error("Not surrounded by '1'", 1));
			}
			else if (ft_valid_char(vars->map[i][j], vars) == false)
				return (false);
			j++;
		}
		if (j != vars->width)
			return (ft_error("Not a rectangle", 1));
		if (vars->map[i][j - 1] != '1')
			return (ft_error("Not surrounded by '1'", 1));
		i++;
	}
	return (true);
}

bool	ft_check_map_chars(t_vars *vars)
{
	if (vars->width < 3 || vars->height < 3)
		return (ft_error("Map too small", 1));
	if (ft_check_map_lines(vars, 0, 0) == false)
		return (false);
	if (vars->amt_e != 1 || vars->amt_p != 1 || vars->amt_c < 1)
		return (ft_error("Wrong ammount of collectables", 1));
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
	ft_free_map(vars);
	free (vars);
	return (exit_code);
}

// bool ft_check_path()



// int	main(void)
// {
// 	t_lst *stack;
// 	t_lst *temp;
// 	int		i;

// 	i = 0;
// 	stack = ft_new_node(-1, 0);
// 	if (!stack)
// 		return (1);
// 	while (i < 15)
// 	{
// 		ft_node_add_back(&stack, ft_new_node(i, 0));
// 		i++;
// 	}
// 	temp = stack;
// 	while (temp)
// 	{
// 		printf("%d##%d\n", temp->row, temp->col);
// 		temp = temp->next;
// 	}
// 	ft_clear_lst(&stack);
// 	if (stack)
// 		printf("error");
	
// }
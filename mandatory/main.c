/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:22:47 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/13 19:20:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	ft_error_exit(char	*error_text, int exit_code)
{
	if (exit_code != 0)
	{
		ft_printf("Error\n");
		ft_printf("%s\n", error_text);
		return (exit_code);
		// exit(exit_code);
	}
	else if (exit_code == 2)
		return (exit_code);
	else
	{
		// exit(exit_code);
		return (0);
	}
}

bool	ft_check_map_name(char *map_name, t_vars *vars)
{
	int	name_len;

	name_len = ft_strlen(map_name);
	if (name_len > 4)
	{
		if (ft_strncmp(map_name + (name_len - 4), ".ber", 4) == 0)
			return (true);
		vars->error_text = "Wrong map Name";
		vars->exit_code = 1;
	}
	return (false);
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
		return (ft_error_exit("Malloc error", 1));
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
		return (ft_error_exit("Error opening the file", 1));
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

bool	ft_check_map(char *map_name, t_vars *vars)
{
	if (ft_check_map_name(map_name, vars) == false)
		return (false);
	if (ft_read_map(map_name, vars) == false)
		return (false);
	int	i = 0;
	while(vars->map[i])
		ft_printf("%s", vars->map[i++]);
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
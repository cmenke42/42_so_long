/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:22:47 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/09 13:21:19 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error_exit(char	*error_text, int exit_code)
{
	if (exit_code != 0)
	{
		ft_printf("Error\n");
		ft_printf("%s\n", error_text);
		exit(exit_code);
	}
	else
	{
		exit(exit_code);
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

bool ft_read_map(char *map_name, t_vars *vars)
{
	int fd;

	fd = open(map_name, O_RDONLY);
	if (fd > -1)
	{
		
	}
	vars->error_text = "Error while reading the map";
	vars->exit_code = 1;
	return (false);
}

bool	ft_check_map(char *map_name, t_vars *vars)
{
	if (ft_check_map_name(map_name, vars) == false)
		return (false);
	if (ft_read_map(map_name, vars) == false)
		return (false);
}


int	main(int argc, char **argv)
{
	t_vars *vars;

	vars = malloc(sizeof(t_vars));
	if (!vars)
		ft_error_exit("Malloc error", 1);
	ft_bzero(vars, sizeof(t_vars));
	if (argc != 2)
		ft_error_exit("Wrong input file", 1);
		
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_free_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 23:17:10 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/17 23:17:31 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
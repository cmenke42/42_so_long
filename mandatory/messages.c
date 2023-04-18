/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:36:27 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/18 23:50:54 by cmenke           ###   ########.fr       */
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
	}
	return (true);
}

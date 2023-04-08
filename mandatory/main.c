/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmenke <cmenke@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:22:47 by cmenke            #+#    #+#             */
/*   Updated: 2023/04/08 21:40:24 by cmenke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

// int	main(int argc, char **argv)
// {
// 	int number;
	
// 	printf("%s\n", argv[argc - 1]);
// }

int	main(void)
{
	t_lst *stack;
	t_lst *temp;
	int		i;

	i = 0;
	stack = ft_new_node(-1, 0);
	if (!stack)
		return (1);
	while (i < 15)
	{
		ft_node_add_back(&stack, ft_new_node(i, 0));
		i++;
	}
	temp = stack;
	while (temp)
	{
		printf("%d##%d\n", temp->row, temp->col);
		temp = temp->next;
	}
	ft_clear_lst(&stack);
	if (stack)
		printf("error");
	
}
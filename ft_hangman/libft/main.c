/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 22:37:01 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/09 09:37:48 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  <stdio.h>
#include "includes/libft.h"

int		main(int argc, char **argv)
{
	int		value;
	t_list	*new;
	
	if(argc != 2)
		return -1;
	// Create new list
	// Generate random numbers and store into some list
	int i = 0;
	while(i < atoi(argv[1]))
	{
		value = rand() % atoi(argv[1]) + 1;
		new = ft_lstnew((int *)value, sizeof(int));
		new = new->next;
		i++;
	}
	// Display the list 
	// Display the backward list
	return 0;
}

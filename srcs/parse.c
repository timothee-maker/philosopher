/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:07:38 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/24 16:15:06 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	parse_arg(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac < 5 || ac > 6)
		exit(0);
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0)
			exit(0);
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				exit(0);
			j++;
		}
		i++;
	}
}

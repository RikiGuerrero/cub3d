/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:45:56 by rguerrer          #+#    #+#             */
/*   Updated: 2024/12/10 11:45:56 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
	if (ac != 2 || ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
	{
		ft_putstr_fd("Error\nInvalid arguments\n", 2);
		return (1);
	}
	else
	{
		if (parse_cub(av[1]) == -1)
			return (1);
		printf("Running game\n");
		game_loop();
		printf("Game over\n");
	}
	return (0);
}
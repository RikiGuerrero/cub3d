/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguerrer <rguerrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:52:01 by rguerrer          #+#    #+#             */
/*   Updated: 2024/12/12 13:32:29 by rguerrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft/includes/libft.h"
# include "MLX42/MLX42.h"

typedef struct	s_map
{
	char	**input;
	char	**map;
}				t_map;

typedef struct s_config
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color[3];
	int		ceiling_color[3];
}				t_config;

typedef struct s_cub
{
	t_map	map;
	t_config	config;
}				t_cub;

// Parsing
int		parse_cub(t_cub *cub, char *file);
void	init_cub(t_cub *cub);
int	ft_checks(t_cub *cub);
char	**ft_map(char **input);
int		ft_valid_map(char **map);
int	ft_parse_textures(t_cub *cub);

#endif
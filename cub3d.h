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
# include "libft/libft.h"
# include "MLX42/MLX42.h"

typedef struct s_cub
{
    
}               t_cub;

typedef struct	s_map
{
    char	**map;
    int     player_x;
    int     player_y;
    int		map_width;
    int		map_height;
}				t_map;


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjimenez <pjimenez@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:52:01 by rguerrer          #+#    #+#             */
/*   Updated: 2025/01/28 13:06:19 by pjimenez         ###   ########.fr       */
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

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

# define S_W 1900
# define S_H 1000
# define TILE_SIZE 30
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4

typedef struct	s_map
{
	char	**input;
	char	**map;
	int		p_x;
	int		p_y;
	char 	init_view;
	int		w_map;
	int		h_map;
}				t_map;

typedef struct s_config
{
	char	*no_texture_path;
	char	*so_texture_path;
	char	*we_texture_path;
	char	*ea_texture_path;
	mlx_texture_t *no_texture;
	mlx_texture_t *so_texture;
	mlx_texture_t *we_texture;
	mlx_texture_t *ea_texture;
	int		floor_color[3];
	int		ceiling_color[3];
}				t_config;

typedef struct s_ray
{
	double	ray_ngl;
	double	distance;
	int		flag;
	double	hor_x;
	double	hor_y;
	double	ver_x;
	double	ver_y;
	int		index;
}				t_ray;

typedef struct s_player
{
	int		plyr_x;
	int		plyr_y;
	double	angle;
	float	fov_rd;
	int		rot;
	int		l_r;
	int		u_d;
}				t_player;

typedef struct s_cub
{
	mlx_image_t *img;
	mlx_t		*mlx_p;
	t_ray		*ray;
	t_player	*ply;
	t_map		*map;
	t_config	config;
}				t_cub;

// Parsing
int		parse_cub(t_cub *cub, char *file);
void	init_cub(t_cub *cub);
int		ft_checks(t_cub *cub);
char	**ft_map(char **input);
int		ft_valid_map(char **map);
int		ft_parse_textures(t_cub *cub);
void 	ft_set_map(t_map *map);
void	free_cub(t_cub *cub);
void 	ft_free_split(char **split);

// Game
void			mlx_key(mlx_key_data_t keydata, void *ml);
void			start_the_game(t_cub *cub);
void			hook(t_cub *cub, double move_x, double move_y);
void			cast_rays(t_cub *cub);
void			ft_exit(t_cub *cub);
float			nor_angle(float angle);
void			render_wall(t_cub *cub, int ray);
int				unit_circle(float angle, char c);
int				inter_check(float angle, float *inter, float *step, int is_horizon);
int				wall_hit(float x, float y, t_cub *cub);
unsigned int	reverse_bytes(unsigned int color);
void			my_mlx_pixel_put(t_cub *mlx, int x, int y, int color);
int				get_rgba(int r, int g, int b, int a);


#endif



// #ifndef CUB3D_H
// # define CUB3D_H

// # include <string.h>
// # include <stdlib.h>
// # include <stdio.h>
// # include <math.h>

// #ifndef M_PI
// #define M_PI 3.14159265358979323846
// #endif
// # include "MLX42/MLX42.h"

// # define S_W 1900
// # define S_H 1000
// # define TILE_SIZE 30
// # define FOV 60
// # define ROTATION_SPEED 0.045
// # define PLAYER_SPEED 4

// typedef struct s_player
// {
// 	int		plyr_x;
// 	int		plyr_y;
// 	double	angle;
// 	float	fov_rd;
// 	int		rot;
// 	int		l_r;
// 	int		u_d;
// }	t_player;

// typedef struct s_ray
// {
// 	double	ray_ngl;
// 	double	distance;
// 	int		flag;	
// }	t_ray;

// typedef struct s_data
// {
// 	char	**map2d;
// 	int		p_x;	
// 	int		p_y;	
// 	int		w_map;	
// 	int		h_map;	
// }	t_data;

// typedef struct s_mlx
// {
// 	mlx_image_t		*img;
// 	mlx_t			*mlx_p;
// 	t_ray			*ray;
// 	t_data			*dt;
// 	t_player		*ply;
// }	t_mlx;



// void mlx_key(mlx_key_data_t keydata, void *ml);
// void	start_the_game(t_data *dt);
// void	hook(t_mlx *mlx, double move_x, double move_y);
// void	cast_rays(t_mlx *mlx);
// void	ft_exit(t_mlx *mlx);
// float	nor_angle(float angle);
// void	render_wall(t_mlx *mlx, int ray);
// #endif
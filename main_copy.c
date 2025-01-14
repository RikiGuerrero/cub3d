// before you start, you need to install the mlx library and you need to install the glfw library
// you need to incude the mlx library in your file
// for compiling the code you need to include the required frameworks and the libmlx.a amd link the glfw library
// the flag (-O3 -ffast-math) is for optimization
// the flag (-framework) is for the required frameworks
// the flag (-lglfw) is for linking the glfw library
// the flag (-L) is for the path to the glfw library
// the flag (-o) is for the name of the executable file
// to run the program (./cub)

// example:
// cc -O3 -ffast-math -framework Cocoa -framework OpenGL -framework IOKit -lglfw (path to libmlx42.a) -L(path to glfw library) cub3d.c -o cub

#include "cub3d.h"
//##############################################################################//
//############################## THE EXITING CODE ##############################//
//##############################################################################//

void	ft_exit(t_mlx *mlx) 		// exit the game
{
	int	i = 0;
	while (mlx->dt->map2d[i])
		free(mlx->dt->map2d[i++]); // free the map line by line
	free(mlx->dt->map2d); // free the map
	free(mlx->dt); // free the data structure
	free(mlx->ply); // free the player structure
	free(mlx->ray); // free the ray structure
	mlx_delete_image(mlx->mlx_p, mlx->img); // delete the image
	mlx_close_window(mlx->mlx_p); // close the window
	mlx_terminate(mlx->mlx_p); // terminate the mlx pointer
	printf("Game closed\n"); // print the message
	exit(0); // exit the game
}


//################################################################################################//
//############################## THE MAIN FUNCTION AND INIT THE MAP ##############################//
//################################################################################################//

t_data *init_argumet()	// init the data structure
{
	t_data *dt = calloc(1, sizeof(t_data)); // init the data structure
	dt->map2d = calloc(10, sizeof(char *)); // init the map
	dt->map2d[0] = strdup("1111111111111111111111111"); //fill the map
	dt->map2d[1] = strdup("1000000000000000000100001");
	dt->map2d[2] = strdup("1001000000000P00000000001");
	dt->map2d[3] = strdup("1001000000000000001000001");
	dt->map2d[4] = strdup("1001000000000000001000001");
	dt->map2d[5] = strdup("1001000000100000001000001");
	dt->map2d[6] = strdup("1001000000000000001000001");
	dt->map2d[7] = strdup("1001000000001000001000001");
	dt->map2d[8] = strdup("1111111111111111111111111");
	dt->map2d[9] = NULL;
	dt->p_y = 3; // player y position in the map
	dt->p_x = 14; // player x position in the map
	dt->w_map = 25; // map width
	dt->h_map = 9; // map height
	return (dt); // return the data structure
}

int main()	// main function
{
	t_data	*data;

	data = init_argumet();	// init the data structure
	start_the_game(data);	// start the game
	return 0;
}
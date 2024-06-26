/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:59:04 by ofadhel           #+#    #+#             */
/*   Updated: 2024/04/14 13:18:02 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	game_loop(t_game *game)
{
	raycasting(game);
	get_frame_time(game);
	mlx_put_image_to_window(game->mlx.init, game->mlx.win,
		game->mlx.img, 0, 0);
	mlx_string_put(game->mlx.init, game->mlx.win,
		15, 10, 0xFFFFFF, game->frame.fps);
	free(game->frame.fps);
	return (0);
}

int	run_mlx(t_mlx *mlx, t_game *game)
{
	mlx_hook(mlx->win, 17, 0, ft_exit, game);
	mlx_hook(mlx->win, 2, 1L << 0, ft_key_press, game);
	mlx_hook(mlx->win, 3, 1L << 1, ft_key_release, game);
	mlx_loop_hook(mlx->init, game_loop, game);
	mlx_put_image_to_window(mlx->init, mlx->win, mlx->img, 0, 0);
	mlx_loop(mlx->init);
	return (1);
}

int	init_mlx(t_game *game)
{
	game->mlx.init = mlx_init();
	if (!game->mlx.init)
		ft_exit(game, 6);
	ft_mlx_xpm_file_to_image(&game->mlx, game);
	game->mlx.win = mlx_new_window(game->mlx.init,
			game->win_width, game->win_height, "cub3D");
	if (!game->mlx.win)
		ft_exit(game, 6);
	game->mlx.img = mlx_new_image(game->mlx.init,
			game->win_width, game->win_height);
	if (!game->mlx.img)
		ft_exit(game, 6);
	game->mlx.address = mlx_get_data_addr(game->mlx.img,
			&game->mlx.bits_per_pixel,
			&game->mlx.size_line, &game->mlx.endian);
	if (!game->mlx.address)
		ft_exit(game, 6);
	run_mlx(&game->mlx, game);
	return (0);
}

void	init_struct(char **av)
{
	t_game	game;

	init(&game);
	parser(av, &game);
	init_camera_position(&game.player, &game.map, &game.camera);
	init_mlx(&game);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf("Error: no map or too many arguments\n");
		return (1);
	}
	init_struct(av);
	return (0);
}

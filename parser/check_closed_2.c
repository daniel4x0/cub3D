/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadhel <ofadhel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:01:51 by ofadhel           #+#    #+#             */
/*   Updated: 2024/04/12 20:51:48 by ofadhel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_space_right_down(t_game *game, int y, int x)
{
	if (x < 0 || y > game->map.height || x > game->map.width || y < 0)
		return ;
	else if (game->map.map[y][x] == '\0')
		return ;
	else if (game->map.map[y][x] == '1')
		return ;
	else if (game->map.map[y][x] == ' ')
	{
		check_space_right_down(game, y, x - 1);
		check_space_right_down(game, y - 1, x);
	}
	else
		ft_exit(game, 3);
}

void	check_space_right_up(t_game *game, int y, int x)
{
	if (x < 0 || y > game->map.height || x > game->map.width || y < 0)
		return ;
	else if (game->map.map[y][x] == '\0')
		return ;
	else if (game->map.map[y][x] == '1')
		return ;
	else if (game->map.map[y][x] == ' ')
	{
		check_space_right_up(game, y, x - 1);
		check_space_right_up(game, y + 1, x);
	}
	else
		ft_exit(game, 3);
}

void	check_closed_edges_2(t_game *game, int y, int x)
{
	if (game->map.map[y][x] == '1' || game->map.map[y][x] == ' ')
		;
	else if (game->map.map[y][x] == ' ')
	{
		check_space_right_up(game, y, x - 1);
		check_space_right_up(game, y + 1, x);
		check_space_right_down(game, y - 1, x);
	}
	else
		ft_exit(game, 3);
}

void	check_closed_edges(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	x = game->map.width - 2;
	while (game->map.map[y])
	{
		if (game->map.map[y][0] == '1' || game->map.map[y][0] == ' ')
			;
		else if (game->map.map[y][0] == ' ')
		{
			check_space_left_up(game, y, 1);
			check_space_left_up(game, y + 1, 0);
			check_space_left_down(game, y - 1, 0);
		}
		else
			ft_exit(game, 3);
		check_closed_edges_2(game, y, x);
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:06:13 by mhummel           #+#    #+#             */
/*   Updated: 2024/07/01 16:03:56 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	**create_visited_array(t_game_state *game)
{
	bool	**visited;
	int		i;

	visited = malloc(game->map.height * sizeof(bool *));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < game->map.height)
	{
		visited[i] = ft_calloc(game->map.width, sizeof(bool));
		if (!visited[i])
		{
			while (i > 0)
				free(visited[--i]);
			free(visited);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

void	free_visited_array(t_game_state *game, bool **visited)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu-chen <yu-chen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:14:00 by lmoran            #+#    #+#             */
/*   Updated: 2024/10/10 12:14:30 by yu-chen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_around(char **map, int y, int x)
{
	if (y - 1 < 0 || x - 1 < 0)
		return (FAIL);
	// if ((y + 1) > ft_strlen(map[y]) || (x + 1) > ft_linelen(map))
	// 	return (FAIL);
	if ((!map[y - 1][x - 1] || map[y - 1][x - 1] == 'E') || (!map[y - 1][x]
			|| map[y - 1][x] == 'E') || (!map[y - 1][x + 1] || map[y - 1][x
			+ 1] == 'E') || (!map[y][x - 1] || map[y][x - 1] == 'E')
		|| (!map[y][x + 1] || map[y][x + 1] == 'E') || (!map[y + 1][x - 1]
			|| map[y + 1][x - 1] == 'E') || (!map[y + 1][x] || map[y
			+ 1][x] == 'E') || (!map[y + 1][x + 1] || map[y + 1][x + 1] == 'E'))
		return (FAIL);
	return (SUCCESS);
}

int	check_map(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_invalid(map[y][x]) == TRUE)
				return (ft_free(map), FAIL);
			if (map[y][x] == '0' || is_player(map[y][x] == TRUE))
				if (check_around(map, y, x) == FAIL)
				{
					// ft_printf("%sMAP ISN'T SURROUNDED BY WALL!%s\n", RED_PR, RST);
					return (ft_free(map), FAIL);
				}
			x++;
		}
		y++;
	}
	ft_free(map);
	return (SUCCESS);
}

// char	**make_square_map(t_data *m)
// {
// 	int		i;
// 	int		j;
// 	char	**sq_map;

// 	i = -1;
// 	m->map_w = get_w(m);
// 	m->map_h = get_h(m);
// 	sq_map = malloc(sizeof(char *) * (m->map_h + 1));
// 	if (!sq_map)
// 		return (NULL);
// 	sq_map[m->map_h] = NULL;
// 	while (++i < m->map_h)
// 	{
// 		j = -1;
// 		sq_map[i] = malloc(sizeof(char) * (m->map_w + 1));
// 		if (!sq_map)
// 			return (NULL);
// 		sq_map[i][m->map_w] = '\0';
// 		while (m->map2d[i][++j])
// 		{
// 			if (ft_isspace(m->map2d[i][j]))
// 				sq_map[i][j] = '1';
// 			else
// 				sq_map[i][j] = m->map2d[i][j];
// 		}
// 		while (j++ < m->map_w)
// 			sq_map[i][j] = '1';
// 	}
// 	return (sq_map);
// }

void	fill_square_map_line(char *sq_map_line, char *map_line, int width)
{
	int	j;

	j = -1;
	while (map_line[++j])
	{
		if (ft_isspace(map_line[j]))
			sq_map_line[j] = '1';
		else
			sq_map_line[j] = map_line[j];
	}
	while (j < width)
		sq_map_line[j++] = '1';
	sq_map_line[width] = '\0';
}

char	**make_square_map(t_data *m)
{
	int		i;
	char	**sq_map;

	m->map_w = get_w(m);
	m->map_h = get_h(m);
	sq_map = malloc(sizeof(char *) * (m->map_h + 1));
	if (!sq_map)
		return (NULL);
	sq_map[m->map_h] = NULL;
	i = -1;
	while (++i < m->map_h)
	{
		sq_map[i] = malloc(sizeof(char) * (m->map_w + 1));
		if (!sq_map[i])
			return (NULL);
		fill_square_map_line(sq_map[i], m->map2d[i], m->map_w);
	}
	return (sq_map);
}

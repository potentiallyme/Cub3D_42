/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu-chen <yu-chen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:03:59 by lmoran            #+#    #+#             */
/*   Updated: 2024/10/15 14:01:08 by yu-chen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	**fill_spaces(char **map)
{
	int		i;
	int		j;
	char	**s;

	i = 0;
	s = ft_strdup_double(map);
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == ' ')
				s[i][j] = 'E';
			j++;
		}
		i++;
	}
	ft_putstr_double(s);
	return (s);
}

int	check_file(t_data *data)
{
	int		i;
	t_file	*tmp;

	i = 0;
	i += check_textures(data, data->linked_file);
	tmp = data->linked_file;
	i += check_rgb(data, tmp, 'F');
	tmp = data->linked_file;
	i += check_rgb(data, tmp, 'C');
	ft_putstr_double(data->map2d);
	ft_putstr_double(data->square_map);
	i += check_map(make_square_map(data, 'E'));
	return (i);
}

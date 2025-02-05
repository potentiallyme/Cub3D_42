/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu-chen <yu-chen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:46:33 by lmoran            #+#    #+#             */
/*   Updated: 2024/10/21 17:41:29 by yu-chen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_if_map(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_invalid(s[i]) == FALSE || s[i] == ' ')
			i++;
		else
			return (FALSE);
	}	
	return (TRUE);
}

t_file	*return_map_start(t_file *file)
{
	t_file	*tmp;

	tmp = file;
	while (tmp)
	{
		if (ft_strchr(tmp->s, '1') && ft_strrchr(tmp->s, '1'))
		{
			if (check_if_map(tmp->s))
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	count_lines(t_file *file)
{
	t_file	*tmp;
	int		c;

	tmp = file;
	c = 0;
	while (tmp)
	{
		c++;
		tmp = tmp->next;
	}
	return (c);
}

char	**return_map(t_data *data)
{
	t_file	*tmp;
	char	**map;
	int		i;

	tmp = return_map_start(data->linked_file);
	if (!tmp)
		return (NULL);
	map = (char **)malloc((count_lines(tmp) + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (tmp)
	{
		if (!tmp->s)
			map[i] = ft_strdup(" ");
		else
			map[i] = ft_strdup(tmp->s);
		tmp = tmp->next;
		i++;
	}
	map[i] = NULL;
	return (map);
}

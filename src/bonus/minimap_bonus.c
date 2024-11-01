/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu-chen <yu-chen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:01:54 by yu-chen           #+#    #+#             */
/*   Updated: 2024/10/15 13:44:39 by yu-chen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	get_mmap_off(t_minimap *mm, int map_size, int pos)
{
	if (pos > mm->view_dist && map_size - pos > mm->view_dist + 1)
		return (pos - mm->view_dist);
	if (pos > mm->view_dist && map_size - pos <= mm->view_dist + 1)
		return (map_size - mm->size);
	return (0);
}

void	ft_free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

char	*add_mmap_line(t_mlx *mlx, t_minimap *mm, int y)
{
	char	*line;
	int		x;

	line = ft_calloc(mm->size + 1, sizeof * line);
	if (!line)
		return (NULL);
	x = 0;
	while (x < S_W && x < mm->size)
	{
		if (y + mm->off_y >= mlx->data.map_h
			|| x + mm->off_x >= mlx->data.map_w)
			line[x] = '\0';
		else if ((int)mlx->ply.ply_x == x + mm->off_x
			&& (int)mlx->ply.ply_y == y + mm->off_y)
			line[x] = 'P';
		else if (mlx->data.square_map[y + mm->off_y][x + mm->off_x] == '1')
			line[x] = '1';
		else if (mlx->data.square_map[y + mm->off_y][x + mm->off_x] == '0')
			line[x] = '0';
		else
			line[x] = '\0';
		x++;
	}
	line[x] = '\0';
	return (line);
}

char	**create_map(t_mlx *mlx, t_minimap *minimap)
{
	char	**mm;
	int		y;

	mm = ft_calloc(minimap->size + 1, sizeof * mm);
	if (!mm)
		return (NULL);
	y = 0;
	while (y < minimap->size)
	{
		mm[y] = add_mmap_line(mlx, minimap, y);
		if (!mm[y])
		{
			ft_free_tab((void **)mm);
			return (NULL);
		}
		y++;
	}
	mm[y] = '\0';
	return (mm);
}

void	draw_border(t_minimap *mm, int color)
{
	int	size;
	int	x;
	int	y;

	size = PIXEL_SIZE + mm->tile_size;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x <= size)
		{
			if (x < 5 || x > size - 5 || y < 5 || y > size - 5)
				draw_pix(mm->img, x, y, color);
			x++;
		}
		y++;
	}
}

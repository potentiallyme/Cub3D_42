/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu-chen <yu-chen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:20:43 by lmoran            #+#    #+#             */
/*   Updated: 2024/10/15 13:42:25 by yu-chen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	*cub_malloc(t_mlx *mlx, int flag, size_t nmemb, size_t size)
{
	char	*ptr;

	if (size == 0)
		return (malloc(0));
	if (nmemb <= 0 && size <= 0)
		return (NULL);
	if (nmemb > (SIZE_MAX / size))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		ft_exit(mlx, "Cub_malloc error", flag, 1);
	ft_bzero(ptr, nmemb * size);
	return ((void *)ptr);
}

void	free_file_list(t_file *file)
{
	t_file	*tmp;

	tmp = file;
	while (file)
	{
		file = file->next;
		free(tmp->s);
		free(tmp);
		tmp = file;
	}
}

void	free_textures(t_data *data)
{
	if (data->north)
		free(data->north);
	if (data->south)
		free(data->south);
	if (data->east)
		free(data->east);
	if (data->west)
		free(data->west);
}

void	free_mlx(t_mlx *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx_p, game->win);
	if (game->mlx_p)
	{
		mlx_destroy_display(game->mlx_p);
		mlx_loop_end(game->mlx_p);
		free(game->mlx_p);
	}
}

void	free_data(t_data *data)
{
	if (data->linked_file)
		free_file_list(data->linked_file);
	if (data->map2d)
		ft_free(data->map2d);
	if (data->square_map)
		ft_free(data->square_map);
	if (data->c_ceiling)
		ft_free(data->c_ceiling);
	if (data->c_floor)
		ft_free(data->c_floor);
	if (data->north)
		free(data->north);
	if (data->south)
		free(data->south);
	if (data->east)
		free(data->east);
	if (data->west)
		free(data->west);
	if (data->ply)
		free(data->ply);
	if (data->fire)
		free(data->fire);
}

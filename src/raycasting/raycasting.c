/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu-chen <yu-chen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:41:11 by yu-chen           #+#    #+#             */
/*   Updated: 2024/10/14 13:20:53 by yu-chen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	set_ray(t_player *ply, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)S_W - 1;
	ray->dir_x = ply->dir_x + ply->plane_x * ray->camera_x;
	ray->dir_y = ply->dir_y + ply->plane_y * ray->camera_x;
	ray->map_x = (int)ply->ply_x;
	ray->map_y = (int)ply->ply_y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

void	set_dda(t_mlx *mlx, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (mlx->ply.ply_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - mlx->ply.ply_x)
			* ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (mlx->ply.ply_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - mlx->ply.ply_y)
			* ray->deltadist_y;
	}
	// printf("px: %f, mx: %i, py: %f, my: %i\n", mlx->ply.ply_x, ray->map_x, mlx->ply.ply_y, ray->map_y);
	// printf("sdx: %f, ddx: %f, sdy: %f, ddy: %f\n", ray->sidedist_x, ray->deltadist_x, ray->sidedist_y, ray->deltadist_y);
}

void	do_dda(t_mlx *mlx, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.1 || ray->map_x < 0.1
			|| ray->map_y > S_H - 0.1 || ray->map_x > S_W - 1.1)
			break ;
		else if (mlx->data.square_map[ray->map_y][ray->map_x] == 'D')
		{
			ray->door = 1;
			hit = 1;
		}
		else if (mlx->data.square_map[ray->map_y][ray->map_x] > '0')
			hit = 1;
		if (is_valid_pos(&mlx->data, ray->map_x, ray->map_y) == FALSE)
			hit = 1;
	}
}

void	calc_line_height(t_ray *ray, t_player *ply)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(S_H / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + S_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + S_H / 2;
	if (ray->draw_end >= S_H)
		ray->draw_end = S_H - 1;
	if (ray->side == 0)
		ray->wall_x = ply->ply_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = ply->ply_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	cast_rays(t_mlx *mlx)
{
	int	x;

	x = 0;
	while (x < S_W)
	{
		init_ray(&mlx->ray);
		set_ray(&mlx->ply, &mlx->ray, x);
		set_dda(mlx, &mlx->ray);
		do_dda(mlx, &mlx->ray);
		calc_line_height(&mlx->ray, &mlx->ply);
		if (BONUS && mlx->ray.door == 1)
            render_door(mlx, &mlx->img);
		set_textures(&mlx, &mlx->tex, &mlx->ray, x);
		x++;
	}
}

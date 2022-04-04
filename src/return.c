/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 15:20:22 by ccottin           #+#    #+#             */
/*   Updated: 2022/04/04 17:29:44 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_map(t_data *d)
{
	int	i;

	if (d->map.map == NULL)
		return ;
	i = 0;
	while (d->map.map[i])
	{
		if (d->map.map[i])
			free(d->map.map[i]);
		i++;
	}
	if (d->map.map)
		free(d->map.map);
}

void	free_all(t_data *d, int code)
{
	if (code == -4)
		return ;
	free_map(d);
	if (d->gnl.line != NULL && code != -3)
		free(d->gnl.line);
	if (d->gnl.leftover != NULL)
		free(d->gnl.leftover);
	if (d->wall.img != NULL)
		mlx_destroy_image(d->win.mlx, d->wall.img);
	if (d->collect.img != NULL)
		mlx_destroy_image(d->win.mlx, d->collect.img);
	if (d->player.img != NULL)
		mlx_destroy_image(d->win.mlx, d->player.img);
	if (d->exit.img != NULL)
		mlx_destroy_image(d->win.mlx, d->exit.img);
	if (d->win.win != NULL)
	{
		mlx_loop_end(d->win.win);
		mlx_destroy_window(d->win.mlx, d->win.win);
	}
	if (d->win.mlx != NULL)
	{
		mlx_destroy_display(d->win.mlx);
		free(d->win.mlx);
	}
}

void	ft_return(t_data *d, int code)
{
	if (code == 0 || code == -2 || code == -3 || code == -4 || code == -5)
	{
		if (code == -2 || code == -3)
			ft_putstr("Error\nMap invalide\n");
		if (code == -4)
			ft_putstr("Error\nPas de fichier\n");
		if (code == -5)
			ft_putstr("Error\nFormat du fichier invalide\n");
		free_all(d, code);
		exit(0);
	}
	if (code == -1)
	{
		ft_putstr("Error\n");
		if (errno != 0)
			perror("so_long ");
		else
			ft_putstr("Fichier vide\n");
		free_all(d, code);
		exit(-1);
	}
}

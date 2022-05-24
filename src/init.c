/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:43:42 by ccottin           #+#    #+#             */
/*   Updated: 2022/05/24 19:06:42 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	put_player(t_data *d)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (d->map.map[j][i] != 'P' && d->map.map[j][i] && j <= d->map.ord_y)
	{
		if (i == d->map.ord_x)
		{
			j++;
			i = 0;
		}
		i++;
	}
	d->player.y = j;
	d->player.x = i;
}

int	init_img(t_data *d)
{
	d->wall.img = mlx_xpm_file_to_image(d->win.mlx, "./img/wall.xpm",
			&d->wall.width, &d->wall.height);
	d->collect.img = mlx_xpm_file_to_image(d->win.mlx, "./img/collect.xpm",
			&d->collect.width, &d->collect.height);
	d->player.img = mlx_xpm_file_to_image(d->win.mlx, "./img/onigiri.xpm",
			&d->player.width, &d->player.height);
	d->exit.img = mlx_xpm_file_to_image(d->win.mlx, "./img/exit1.xpm",
			&d->exit.width, &d->exit.height);
	if (d->wall.img == NULL || d->exit.img == NULL || d->player.img == NULL
		|| d->collect.img == NULL)
		return (-1);
	print_map(d);
	return (0);
}

int	init_window(t_data *d)
{
	d->win.mlx = mlx_init();
	if (!d->win.mlx)
		return (-1);
	mlx_get_screen_size(d->win.mlx, &(d->win.width), &(d->win.height));
	if (d->win.width < (d->map.ord_x * 40)
		&& d->win.height < (d->map.ord_y * 40))
		d->win.win = mlx_new_window(d->win.mlx, d->win.width,
				(d->win.height - 80), "so_long");
	else if (d->win.width < (d->map.ord_x * 40))
		d->win.win = mlx_new_window(d->win.mlx, d->win.width,
				(((d->map.ord_y + 1) * 40) + 1), "so_long");
	else if (d->win.height < (d->map.ord_y * 40))
		d->win.win = mlx_new_window(d->win.mlx, ((d->map.ord_x * 40) + 1),
				d->win.height, "so_long");
	else
		d->win.win = mlx_new_window(d->win.mlx, ((d->map.ord_x * 40) + 1),
				(((d->map.ord_y + 1) * 40) + 1), "so_long");
	if (!d->win.win)
		return (-1);
	if (init_img(d) == -1)
		return (-1);
	mlx_hook(d->win.win, 3, 1L << 1, handle_key, d);
	mlx_hook(d->win.win, 17, 1L << 2, handle_close, d);
	mlx_loop(d->win.mlx);
	return (0);
}

void	set_zero(t_data *d)
{
	errno = 0;
	d->win.mlx = NULL;
	d->win.win = NULL;
	d->wall.img = NULL;
	d->collect.img = NULL;
	d->collect.count = 0;
	d->player.img = NULL;
	d->player.count = 0;
	d->exit.img = NULL;
	d->exit.count = 0;
	d->map.map = NULL;
	d->player.x = 0;
	d->player.y = 0;
	d->gnl.leftover = NULL;
	d->gnl.line = NULL;
	d->move = 0;
	d->win.width = 0;
	d->win.height = 0;
	d->map.start_h = 0;
	d->map.start_w = 0;
	d->map.end_h = 0;
	d->map.end_w = 0;
	d->map.map = NULL;
}

int	ft_init(char *av1, t_data *d)
{
	int	i;

	set_zero(d);
	i = check_map(av1, d);
	if (i != 0)
		return (i);
	put_player(d);
	if (init_window(d) == -1)
		return (-1);
	return (0);
}

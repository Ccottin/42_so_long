/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:46:38 by ccottin           #+#    #+#             */
/*   Updated: 2022/04/04 17:23:41 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	put_line(char *str, int y, t_data *d, int i)
{
	int	j;

	j = d->map.start_w;
	if (d->map.end_w == 0)
		d->map.end_w = d->map.ord_x;
	while (str[j] && str[j] != '\n' && j <= d->map.end_w)
	{
		if (str[j] == '1')
			mlx_put_image_to_window(d->win.mlx, d->win.win,
				d->wall.img, (i * 40), (y * 40));
		if (str[j] == 'P')
			mlx_put_image_to_window(d->win.mlx, d->win.win,
				d->player.img, (i * 40), (y * 40));
		if (str[j] == 'E')
			mlx_put_image_to_window(d->win.mlx, d->win.win,
				d->exit.img, (i * 40), (y * 40));
		if (str[j] == 'F')
			mlx_put_image_to_window(d->win.mlx, d->win.win,
				d->player.img, (i * 40), (y * 40));
		if (str[j] == 'C')
			mlx_put_image_to_window(d->win.mlx, d->win.win,
				d->collect.img, (i * 40), (y * 40));
		j++;
		i++;
	}
}

void	scrolling_w(t_data *d)
{
	int	mid;
	int	nb;

	nb = d->win.width / 40;
	mid = nb / 2;
	d->map.start_w = d->player.x - mid;
	d->map.end_w = d->player.x + mid;
	if (d->map.start_w < 0)
	{
		d->map.start_w = 0;
		d->map.end_w = nb;
	}
	if (d->map.end_w > d->map.ord_x)
	{
		d->map.start_w = d->map.ord_x - nb;
		d->map.end_w = d->map.ord_x;
	}
}

void	scrolling_h(t_data *d)
{
	int	mid;
	int	nb;

	nb = (d->win.height - 80) / 40;
	mid = nb / 2;
	d->map.start_h = d->player.y - mid;
	d->map.end_h = d->player.y + mid;
	if (d->map.start_h < 0)
	{
		d->map.start_h = 0;
		d->map.end_h = nb;
	}
	if (d->map.end_h > d->map.ord_y)
	{
		d->map.start_h = d->map.ord_y - nb + 1;
		d->map.end_h = d->map.ord_y;
	}
}

void	print_map(t_data *d)
{
	int	i;
	int	j;
	int	y;

	if (d->win.width < (d->map.ord_x * 40))
		scrolling_w(d);
	if (d->win.height < (d->map.ord_y * 40))
		scrolling_h(d);
	y = 0;
	j = d->map.start_h;
	if (d->map.end_h == 0)
		d->map.end_h = d->map.ord_y;
	while (d->map.map[j] && j <= d->map.end_h)
	{
		i = 0;
		put_line(d->map.map[j], y, d, i);
		j++;
		y++;
	}
}

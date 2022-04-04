/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:02:51 by ccottin           #+#    #+#             */
/*   Updated: 2022/04/04 18:16:33 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	print_count(t_data *d)
{
	ft_putstr("Nombre de coup : ");
	ft_putnbr(d->move);
	ft_putstr("\n");
}

int	check_case(t_data *d, int i, int j)
{
	if (d->map.map[j][i] == '1')
		return (1);
	if (d->map.map[j][i] == 'C')
		d->collect.count--;
	if (d->map.map[j][i] == 'E' && d->collect.count == 0)
	{
		d->map.map[j][i] = 'P';
		mlx_destroy_image(d->win.mlx, d->player.img);
		d->player.img = mlx_xpm_file_to_image(d->win.mlx,
				"./img/onishock.xpm", &d->player.width,
				&d->player.height);
		d->move++;
		print_count(d);
		print_map(d);
		ft_return(d, 0);
	}
	else if (d->map.map[j][i] == 'E' && d->collect.count != 0)
		d->map.map[j][i] = 'F';
	else
		d->map.map[j][i] = 'P';
	d->player.x = i;
	d->player.y = j;
	return (0);
}

int	move_player(int keycode, t_data *d)
{
	int	c;
	int	i;
	int	j;

	i = d->player.x;
	j = d->player.y;
	c = 0;
	if (keycode == 100)
		c = check_case(d, d->player.x + 1, d->player.y);
	if (keycode == 97)
		c = check_case(d, d->player.x - 1, d->player.y);
	if (keycode == 115)
		c = check_case(d, d->player.x, d->player.y + 1);
	if (keycode == 119)
		c = check_case(d, d->player.x, d->player.y - 1);
	if (c == 0)
	{
		if (d->map.map[j][i] == 'F')
			d->map.map[j][i] = 'E';
		else
			d->map.map[j][i] = '0';
		d->move++;
		print_count(d);
	}
	return (0);
}

int	handle_close(t_data *d)
{
	ft_return(d, 0);
	return (0);
}

int	handle_key(int keycode, t_data *d)
{
	if (keycode == 65307)
		ft_return(d, 0);
	if (keycode == 100 || keycode == 97 || keycode == 115 || keycode == 119)
	{
		move_player(keycode, d);
		mlx_clear_window(d->win.mlx, d->win.win);
		print_map(d);
	}
	return (0);
}

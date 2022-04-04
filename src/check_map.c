/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:04:15 by ccottin           #+#    #+#             */
/*   Updated: 2022/04/04 18:11:05 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_only_one(char *str, int x)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '1')
		i++;
	if (i != x)
		return (-2);
	return (0);
}

int	parse_map(char *av1, t_data *d)
{
	int		i;
	int		fd;

	fd = open(av1, O_RDONLY);
	if (!fd)
		return (-1);
	d->map.map = ft_calloc(d->map.ord_y + 2, sizeof(char *));
	if (!d->map.map)
		return (-1);
	i = 0;
	while (i <= d->map.ord_y)
	{
		d->map.map[i] = get_next_line(fd, 100, d);
		if (!d->map.map[i])
			return (-1);
		if (i == 0 || i == d->map.ord_y)
		{
			if (check_only_one(d->map.map[i], d->map.ord_x) != 0)
				return (-3);
		}
		i++;
	}
	get_next_line(fd, 100, d);
	close(fd);
	return (0);
}

int	check_line(char *str, t_data *d)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if ((i == 0 || i == d->map.ord_x) && str[i] != '1')
			return (-2);
		else if (str[i] == 'C')
			d->collect.count++;
		else if (str[i] == 'E')
			d->exit.count++;
		else if (str[i] == 'P')
			d->player.count++;
		else
		{
			if (str[i] != '0' && str[i] != '1' && str[i] != '\n')
				return (-2);
		}	
		i++;
	}
	if (i != d->map.ord_x && str[0] != '\n')
		return (-2);
	return (0);
}

int	check_rectangle(char *av1, t_data *d, int ret, int fd)
{
	char	*str;

	fd = open(av1, O_RDONLY);
	if (!fd || fd == -1)
		return (-1);
	str = get_next_line(fd, 100, d);
	if (!str)
		return (-1);
	while (str[d->map.ord_x] && str[d->map.ord_x] != '\n')
		d->map.ord_x++;
	while (str != NULL)
	{
		free(str);
		str = get_next_line(fd, 100, d);
		if (str == NULL)
			break ;
		ret = check_line(str, d);
		if (ret != 0)
			return (ret);
		if (str[0] != '\n')
			d->map.ord_y++;
	}
	close(fd);
	free(str);
	return (0);
}

int	check_map(char *av1, t_data *d)
{
	int	i;
	int	ret;
	int	fd;

	i = 0;
	while (av1[i])
		i++;
	if (av1[i - 4] != '.' || av1[i - 3] != 'b' || av1[i - 2] != 'e'
		|| av1[i - 1] != 'r')
		return (-5);
	d->map.ord_x = 0;
	d->map.ord_y = 0;
	ret = 0;
	fd = 0;
	i = check_rectangle(av1, d, ret, fd);
	if (i != 0)
		return (i);
	if (d->collect.count == 0 || d->exit.count == 0 || d->player.count != 1)
		return (-2);
	i = parse_map(av1, d);
	if (i != 0)
		return (i);
	return (0);
}

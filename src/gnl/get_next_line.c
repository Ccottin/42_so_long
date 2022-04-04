/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:08:26 by ccottin           #+#    #+#             */
/*   Updated: 2022/04/04 17:10:12 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	*ft_return1(t_data *d, int mark)
{
	if (mark == -1)
	{
		if (d->gnl.leftover)
			free(d->gnl.leftover);
		if (d->gnl.line)
			free(d->gnl.line);
		return (NULL);
	}
	else
	{
		if (!d->gnl.leftover && mark == -2
			&& ft_strcmp(d->gnl.line, "") == 0)
		{
			free(d->gnl.line);
			d->gnl.line = NULL;
		}
		return (d->gnl.line);
	}
}

char	*cut_leftover(t_data *d, int bsn)
{
	int	i;
	int	y;

	y = ft_strlen(d->gnl.line, bsn);
	if (y != 0 && bsn != -1)
	{
		d->gnl.leftover = ft_calloc(y, 1);
		if (!d->gnl.leftover)
			return (NULL);
		i = 0;
		bsn++;
		while (i < y)
		{
			d->gnl.leftover[i] = d->gnl.line[bsn];
			i++;
			bsn++;
		}
		bsn = bsn - i;
		d->gnl.line[bsn] = '\0';
	}
	return (d->gnl.line);
}

int	get_str(int fd, char **str, int buff)
{
	int		ret;

	*str = ft_calloc(buff + 1, 1);
	if (!str)
		return (-1);
	ret = read(fd, *str, buff);
	return (ret);
}

int	get_line(int fd, t_data *d, int buff)
{
	char	*str;
	int		mark;
	int		i;

	mark = -1;
	i = 0;
	while (mark != 0)
	{
		while (d->gnl.line[i] != '\n' && i < ft_strlen(d->gnl.line, 0))
			i++;
		if (d->gnl.line[i] == '\n')
			mark = 0;
		else
		{
			mark = get_str(fd, &str, buff);
			if (mark == -1)
				return (-1);
			d->gnl.line = ft_strcat(d->gnl.line, str);
			if (mark == 0)
				i = -2;
		}
	}
	return (i);
}

char	*get_next_line(int fd, int buff, t_data *d)
{
	int			i;

	d->gnl.line = "";
	if (fd < 0 || !buff || read(fd, d->gnl.line, 0) == -1)
		return (NULL);
	d->gnl.line = NULL;
	if (!d->gnl.leftover)
		get_str(fd, &d->gnl.line, buff);
	else
		d->gnl.line = ft_copy(d);
	if (d->gnl.line == NULL)
		return (ft_return1(d, -1));
	i = get_line(fd, d, buff);
	if (i == -1)
		return (ft_return1(d, -1));
	if (i == -2)
		return (ft_return1(d, -2));
	d->gnl.line = cut_leftover(d, i);
	if (d->gnl.line == NULL)
		return (ft_return1(d, -1));
	return (ft_return1(d, 1));
}

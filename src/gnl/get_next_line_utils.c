/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:12:56 by ccottin           #+#    #+#             */
/*   Updated: 2022/02/15 11:16:44 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_strlen(char *str, int start)
{
	int	i;

	i = start;
	while (str[i])
		i++;
	return (i - start);
}

char	*ft_copy(t_data *d)
{
	char	*ret;
	int		i;

	ret = ft_calloc(ft_strlen(d->gnl.leftover, 0) + 1, 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (d->gnl.leftover[i])
	{
		ret[i] = d->gnl.leftover[i];
		i++;
	}
	free(d->gnl.leftover);
	d->gnl.leftover = NULL;
	return (ret);
}

void	*ft_calloc1(size_t size, size_t mem)
{
	char	*str;
	size_t	i;

	str = malloc(size * mem);
	if (!str)
		return (NULL);
	i = 0;
	while (i < size * mem)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

char	*ft_strcat(char *s1, char *s2)
{
	int		i;
	int		y;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	ret = ft_calloc(ft_strlen(s1, 0) + ft_strlen(s2, 0) + 1, 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	y = 0;
	while (s2[y])
	{
		ret[i] = s2[y];
		i++;
		y++;
	}
	free(s1);
	free(s2);
	return (ret);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]))
		i++;
	if (s1[i] > s2[i] || s1[i] < s2[i])
		return (1);
	else
		return (0);
}

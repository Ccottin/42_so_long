/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:08:35 by ccottin           #+#    #+#             */
/*   Updated: 2022/04/04 17:21:09 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*s1;

	i = 0;
	s1 = (unsigned char *)s;
	while (i < n)
	{
		s1[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}

int	ft_putstr(char *s)
{
	size_t	i;
	int		intnutile;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
		i++;
	intnutile = write(1, s, i);
	return (intnutile);
}

int	ft_putchar(unsigned char c)
{
	int	intnutile;

	intnutile = write (1, &c, 1);
	return (intnutile);
}

int	ft_putnbr(int n)
{
	int	intnutile;

	if (n == -2147483648)
		intnutile = write(1, "-2147483648", 11);
	else if (n < 0)
	{
		n = n * -1;
		intnutile = ft_putchar('-');
		ft_putnbr(n);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		intnutile = ft_putchar(n % 10 + 48);
	}
	else
		intnutile = ft_putchar(n + 48);
	return (intnutile);
}

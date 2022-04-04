/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccottin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:27:39 by ccottin           #+#    #+#             */
/*   Updated: 2022/04/04 18:27:41 by ccottin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

typedef struct s_win {
	void	*mlx;
	void	*win;
	int		width;
	int		height;
}		t_win;

typedef struct s_img {
	void	*img;
	int		width;
	int		height;
	int		x;
	int		y;
	int		count;
}		t_img;

typedef struct s_map {
	char	**map;
	int		ord_x;
	int		ord_y;
	int		start_h;
	int		end_h;
	int		start_w;
	int		end_w;
}		t_map;

typedef struct s_gnl{
	char	*leftover;
	char	*line;
}		t_gnl;

typedef struct s_data {
	t_win	win;
	t_map	map;
	t_img	wall;
	t_img	collect;
	t_img	player;
	t_img	exit;
	t_gnl	gnl;
	int		move;

}		t_data;

void	print_map(t_data *d);
void	ft_return(t_data *d, int code);
void	*ft_calloc(size_t nmemb, size_t size);

int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str, int start);
int		ft_putnbr(int n);
int		ft_putstr(char *s);
int		handle_close(t_data *d);
int		ft_init(char *av1, t_data *d);
int		check_map(char *av1, t_data *d);
int		handle_key(int keycode, t_data *d);

char	*get_next_line(int fd, int buff, t_data *d);
char	*ft_copy(t_data *d);
char	*ft_strcat(char *s1, char *s2);

#endif

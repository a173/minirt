/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <acaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 21:32:28 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/27 22:25:24 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	add_to_bit(char *t, int i, int k)
{
	t[i] = k % 256;
	t[i + 1] = k / 256 % 256;
	t[i + 2] = k / 256 / 256 % 256;
	t[i + 3] = k / 256 / 256 / 256;
}

static void	filehead(int fd, t_mlx *mlx)
{
	int		i;
	char	t[14];

	i = -1;
	while (++i < 14)
		t[i] = 0;
	t[0] = 66;
	t[1] = 77;
	t[10] = 54;
	add_to_bit(t, 2, mlx->all->y * mlx->all->x);
	write(fd, t, 14);
}

static void	infohead(int fd, t_mlx *mlx)
{
	int		i;
	char	t[40];

	i = -1;
	while (++i < 40)
		t[i] = 0;
	t[0] = 40;
	t[12] = 1;
	t[14] = 32;
	add_to_bit(t, 4, mlx->all->x);
	add_to_bit(t, 8, mlx->all->y);
	write(fd, t, 40);
}

static void	color_table(int fd, t_mlx *mlx)
{
	int y;
	int x;

	y = mlx->all->y;
	while (y-- && (x = -1))
		while (++x < mlx->all->x)
			write(fd, (mlx->addr + (y * mlx->line + x * (mlx->pixel / 8))), 4);
}

int			create_bmp(t_mlx *mlx)
{
	int fd;

	if ((fd = open(BMP, O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		return (error_logs(-6));
	filehead(fd, mlx);
	infohead(fd, mlx);
	color_table(fd, mlx);
	close(fd);
	return (0);
}

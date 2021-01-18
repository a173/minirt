/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:01:30 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/21 21:01:31 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "get_next_line.h"

static t_cvc	canvas(t_all *a, double *x, double *y)
{
	return ((t_cvc) {*x * (1.0 / a->x) * a->x / a->y, *y * (1.0 / a->y), 1});
}

void			feel_screen(t_mlx *mlx)
{
	double x;
	double y;
	double pov;

	mlx->y = -1;
	pov = 2 * tan(mlx->all->camera->g / 2 * M_PI / 180);
	while (++mlx->y < mlx->all->y && (mlx->x = -1))
	{
		y = pov * ((mlx->all->y / 2) - mlx->y);
		while (++mlx->x < mlx->all->x)
		{
			x = pov * (mlx->x - (mlx->all->x / 2));
			my_mlx_pixel_put(mlx, &(mlx)->x, &(mlx)->y,
				rgb_to_int(traceray(mlx->all->camera,
					cam_look(mlx->all->camera->v,
						canvas(mlx->all, &x, &y)), mlx->all)));
		}
	}
}

static void		window(t_all *a)
{
	t_mlx mlx;

	!(mlx.mlx = mlx_init()) ? key(53, &mlx) : 0;
	mlx_get_screen_size(&mlx.mlx, &mlx.x, &mlx.y);
	a->y > mlx.y ? a->x = mlx.x : a->x;
	a->y > mlx.y ? a->y = mlx.y : a->y;
	!(mlx.win = mlx_new_window(mlx.mlx, a->x, a->y, TIT)) ? key(53, &mlx) : 0;
	mlx.all = a;
	mlx.img = mlx_new_image(mlx.mlx, a->x, a->y);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.pixel, &mlx.line, &mlx.end);
	feel_screen(&mlx);
	a->save && !create_bmp(&mlx) ? key(53, &mlx) : 0;
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_key_hook(mlx.win, key, &mlx);
	mlx_hook(mlx.win, 17, 0L, key_destroy, a);
	mlx_loop(mlx.mlx);
}

static int		open_file(char *name, int *fd, int i)
{
	if ((*fd = open(name, O_RDONLY)) <= 0)
		return (error_logs(-2));
	while (name[i] != '.' && name[i])
		i++;
	if (!name[i] || (!i || ft_strncmp(&name[i], ".rt", 3))
		|| (next(3, &i) && skip(name, &i) && name[i]))
	{
		close(*fd);
		return (error_logs(-2));
	}
	return (1);
}

int				main(int argc, char **argv)
{
	int		fd;
	t_all	*all;

	if (argc > 3)
		return (error_logs(-3));
	if (open_file(argv[1], &fd, 0) != 1)
		return (0);
	if (!(all = parser(fd)))
	{
		close(fd);
		return (0);
	}
	if (argv[2] && !ft_strncmp(argv[2], "--save", ft_strlen(argv[2])))
		all->save = 1;
	else if (argv[2])
		return (!is_free(all) && error_logs(-5));
	window(all);
	return (0);
}

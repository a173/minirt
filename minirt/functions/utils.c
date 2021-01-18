/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:45:40 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/21 21:45:41 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

void	my_mlx_pixel_put(t_mlx *d, int *x, int *y, int rgb)
{
	char *dst;

	dst = d->addr + (*y * d->line + *x * (d->pixel / 8));
	*(int*)dst = rgb;
}

int		rgb_to_int(t_cvc rgb)
{
	rgb.x > 255 ? rgb.x = 255 : 0;
	rgb.y > 255 ? rgb.y = 255 : 0;
	rgb.z > 255 ? rgb.z = 255 : 0;
	return ((int)rgb.x * 65536 + (int)rgb.y * 256 + (int)rgb.z);
}

t_cvc	cam_look(t_cvc *v, t_cvc d)
{
	t_cvc x;
	t_cvc y;
	t_cvc z;

	z = *v;
	x = cross((t_cvc) {0, 1, 0}, z);
	y = cross(z, x);
	return ((t_cvc) {d.x * x.x + d.y * x.y + d.z * x.z,
					d.x * y.x + d.y * y.y + d.z * y.z,
					d.x * z.x + d.y * z.y + d.z * z.z});
}

int		key(int c, t_mlx *m)
{
	if (c == 53 && !is_free(m->all))
		exit(1);
	else if (m->all->c_cam > 1 && c == 123)
		m->all->camera = m->all->camera->prev;
	else if (m->all->c_cam > 1 && c == 124)
		m->all->camera = m->all->camera->next;
	else if (c == 125 && (m->all->camera->g += 10))
		m->all->camera->g = m->all->camera->g <= 170 ?
			m->all->camera->g : 170;
	else if (c == 126 && (m->all->camera->g -= 10))
		m->all->camera->g = m->all->camera->g >= 10 ?
			m->all->camera->g : 10;
	else
		return (0);
	mlx_clear_window(m->mlx, m->win);
	feel_screen(m);
	mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
	return (1);
}

int		key_destroy(t_all *all)
{
	printf("Exit close");
	is_free(all);
	exit(1);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_head.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 15:56:30 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/21 16:00:30 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	write_scr(t_all *a, char *l, int i)
{
	if (a->x != -1 || a->y != -1)
		return (0);
	skip(l, &i);
	if (!ft_isdigit(l[i]) || !next(ft_atoi(&l[i], &a->x), &i) || a->x <= 0)
		return (0);
	skip(l, &i);
	if (!ft_isdigit(l[i]) || !next(ft_atoi(&l[i], &a->y), &i) || a->y <= 0)
		return (0);
	if (skip(l, &i) && l[i])
		return (0);
	return (1);
}

int	write_amb(t_all *a, char *l, int i)
{
	if (a->light != -1 || a->rgb)
		return (0);
	skip(l, &i);
	if (!next(ft_atof(&l[i], &a->light), &i)
		|| a->light < 0 || a->light > 1)
		return (0);
	skip(l, &i);
	if (!next(ft_atoc(&l[i], &a->rgb), &i))
		return (0);
	if (skip(l, &i) && l[i])
		return (0);
	return (1);
}

int	write_camera(t_all *a, char *l, int i)
{
	t_camera *c;

	if (!(c = add_camera_back(&a->camera, init_camera())))
		return (-1);
	a->c_cam++;
	skip(l, &i);
	if (!next(ft_atov(&l[i], &c->c), &i))
		return (0);
	skip(l, &i);
	if (!next(ft_atov(&l[i], &c->v), &i) || c->v->x < -1 || c->v->x > 1
		|| c->v->y < -1 || c->v->y > 1 || c->v->z < -1 || c->v->z > 1)
		return (0);
	c->v->y = -c->v->y;
	skip(l, &i);
	if (!ft_isdigit(l[i]) || !next(ft_atoi(&l[i], &c->g), &i)
		|| c->g < 0 || c->g > 180)
		return (0);
	if (skip(l, &i) && l[i])
		return (0);
	return (1);
}

int	write_light(t_all *a, char *l, int i)
{
	t_objects *o;

	if (!(o = add_object_back(&a->object, init_object(1))))
		return (-1);
	skip(l, &i);
	if (!next(ft_atov(&l[i], &o->c1), &i))
		return (0);
	skip(l, &i);
	if (!ft_isdigit(l[i]) || !next(ft_atof(&l[i], &o->d), &i)
		|| o->d < 0 || o->d > 1)
		return (0);
	skip(l, &i);
	if (!next(ft_atoc(&l[i], &o->rgb), &i))
		return (0);
	if (skip(l, &i) && l[i])
		return (0);
	return (1);
}

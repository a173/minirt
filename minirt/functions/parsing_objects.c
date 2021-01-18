/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 20:51:09 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/21 20:51:11 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	write_sphere(t_all *a, char *l, int i)
{
	t_objects *o;

	if (!(o = add_object_back(&a->object, init_object(2))))
		return (-1);
	skip(l, &i);
	if (!next(ft_atov(&l[i], &o->c1), &i))
		return (0);
	skip(l, &i);
	if (!ft_isdigit(l[i]) || !next(ft_atof(&l[i], &o->d), &i))
		return (0);
	o->d = o->d / 2;
	skip(l, &i);
	if (!next(ft_atoc(&l[i], &o->rgb), &i))
		return (0);
	if (skip(l, &i) && l[i])
		return (0);
	if (!(o->nv = new_cvc(o->c1->x, o->c1->y, o->c1->z)))
		return (-1);
	return (1);
}

int	write_plane(t_all *a, char *l, int i)
{
	t_objects *o;

	if (!(o = add_object_back(&a->object, init_object(3))))
		return (-1);
	skip(l, &i);
	if (!next(ft_atov(&l[i], &o->c1), &i))
		return (0);
	skip(l, &i);
	if (!next(ft_atov(&l[i], &o->nv), &i) || !v_o(o))
		return (0);
	skip(l, &i);
	if (!next(ft_atoc(&l[i], &o->rgb), &i))
		return (0);
	if (skip(l, &i) && l[i])
		return (0);
	return (1);
}

int	write_square(t_all *a, char *l, int i)
{
	t_objects *o;

	if (!(o = add_object_back(&a->object, init_object(4))))
		return (-1);
	skip(l, &i);
	if (!next(ft_atov(&l[i], &o->c1), &i))
		return (0);
	skip(l, &i);
	if (!next(ft_atov(&l[i], &o->nv), &i) || !v_o(o))
		return (0);
	skip(l, &i);
	if (!ft_isdigit(l[i]) || !next(ft_atof(&l[i], &o->d), &i))
		return (0);
	o->d = o->d / 2;
	skip(l, &i);
	if (!next(ft_atoc(&l[i], &o->rgb), &i))
		return (0);
	if (skip(l, &i) && l[i])
		return (0);
	return (1);
}

int	write_cylinder(t_all *a, char *l, int i)
{
	t_objects *o;

	if (!(o = add_object_back(&a->object, init_object(5))))
		return (-1);
	skip(l, &i);
	if (!next(ft_atov(&l[i], &o->c1), &i))
		return (0);
	skip(l, &i);
	if (!next(ft_atov(&l[i], &o->nv), &i) || !v_o(o))
		return (0);
	skip(l, &i);
	if (!ft_isdigit(l[i]) || !next(ft_atof(&l[i], &o->d), &i))
		return (0);
	o->d = o->d / 2;
	skip(l, &i);
	if (!ft_isdigit(l[i]) || !next(ft_atof(&l[i], &o->h), &i))
		return (0);
	skip(l, &i);
	if (!next(ft_atoc(&l[i], &o->rgb), &i))
		return (0);
	if (skip(l, &i) && l[i])
		return (0);
	return (1);
}

int	write_triangle(t_all *a, char *l, int i)
{
	t_objects *o;

	if (!(o = add_object_back(&a->object, init_object(6))))
		return (-1);
	skip(l, &i);
	if (!next(ft_atov(&l[i], &o->c1), &i))
		return (0);
	skip(l, &i);
	if (!next(ft_atov(&l[i], &o->c2), &i))
		return (0);
	skip(l, &i);
	if (!next(ft_atov(&l[i], &o->c3), &i))
		return (0);
	skip(l, &i);
	if (!next(ft_atoc(&l[i], &o->rgb), &i))
		return (0);
	if (!(o->nv = nv(*o)))
		return (-1);
	if (skip(l, &i) && l[i])
		return (0);
	return (1);
}

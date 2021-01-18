/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:07:19 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/21 21:07:20 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	cylinder2(t_cvc *camera, double *x, t_cvc *d, t_objects *o)
{
	t_cvc	t[2];
	t_cvc	k;
	double	d1;

	t[0] = v_new(*d, v_num(o->nv, v_scalar(*d, *o->nv), '*'), '-');
	t[1] = v_new(v_new(*camera, *o->c1, '-'), v_num(o->nv,
		v_scalar(v_new(*camera, *o->c1, '-'), *o->nv), '*'), '-');
	k = (t_cvc) {v_scalar(t[0], t[0]), 2 * v_scalar(t[0], t[1]),
		v_scalar(t[1], t[1]) - pow(o->d, 2)};
	x[2] = -1;
	if ((d1 = pow(k.y, 2) - 4 * k.x * k.z) > 0)
	{
		x[0] = (-k.y + sqrt(d1)) / (2 * k.x);
		x[1] = (-k.y - sqrt(d1)) / (2 * k.x);
	}
	else if (d1 == 0)
	{
		x[0] = -k.y / (2 * k.x);
		x[1] = x[0];
	}
	else
		return (0);
	return (1);
}

double		cylinder(t_cvc *camera, t_cvc *d, t_objects *o, double t_min)
{
	double	x[3];
	t_cvc	t[2];

	if (!cylinder2(camera, x, d, o))
		return (x[2]);
	t[0] = v_new(*o->c1, v_num(o->nv, o->h / 2, '*'), '-');
	t[1] = v_new(*o->c1, v_num(o->nv, o->h / 2, '*'), '+');
	if (x[0] >= t_min && v_scalar(*o->nv, v_new(v_new(*camera,
		v_num(d, x[0], '*'), '+'), t[0], '-')) > 0 && v_scalar(*o->nv,
			v_new(v_new(*camera, v_num(d, x[0], '*'), '+'), t[1], '-')) < 0)
		x[2] = x[0];
	if (x[1] >= t_min && v_scalar(*o->nv, v_new(v_new(*camera,
		v_num(d, x[1], '*'), '+'), t[0], '-')) > 0 && v_scalar(*o->nv,
			v_new(v_new(*camera, v_num(d, x[1], '*'), '+'), t[1], '-')) < 0)
		x[2] = x[0] < x[1] ? x[0] : x[1];
	return (x[2]);
}

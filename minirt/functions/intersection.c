/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 21:07:19 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/21 21:07:20 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		sphere(t_cvc *camera, t_cvc *d, t_objects *o, double t_min)
{
	double	x[3];
	double	d1;
	t_cvc	k;
	t_cvc	oc;

	oc = v_new(*camera, *o->c1, '-');
	k.x = v_scalar(*d, *d);
	k.y = 2 * v_scalar(oc, *d);
	k.z = v_scalar(oc, oc) - pow(o->d, 2);
	x[2] = -1;
	if ((d1 = pow(k.y, 2) - 4 * k.x * k.z) > 0)
	{
		x[0] = (-k.y + sqrt(d1)) / (2 * k.x);
		x[1] = (-k.y - sqrt(d1)) / (2 * k.x);
		x[0] < t_min && x[0] > x[1] ? 0 : (x[2] = x[0]);
		x[1] >= t_min && x[0] > x[1] ? (x[2] = x[1]) : 0;
	}
	else if (d1 == 0)
	{
		x[0] = -k.y / (2 * k.x);
		x[0] < t_min ? 0 : (x[2] = x[0]);
	}
	return (x[2]);
}

double		plane(t_cvc *c, t_cvc *d, t_objects *o, double t_min)
{
	double dot;
	double x;

	if (!(dot = v_scalar(*o->nv, *d)))
		return (-1);
	return ((x = v_scalar(*o->nv, v_new(*o->c1, *c, '-')) / dot) >= t_min
		? x : -1);
}

double		square(t_cvc *camera, t_cvc *d, t_objects *o, double t_min)
{
	t_cvc	p;
	t_cvc	sq;
	double	x;

	x = plane(camera, d, o, t_min);
	p = v_new(*camera, v_num(d, x, '*'), '+');
	sq = v_new(p, *o->c1, '-');
	return (x >= t_min && fabs(sq.x) <= o->d && fabs(sq.y) <= o->d
		&& fabs(sq.z) <= o->d ? x : -1);
}

double		triangle(t_cvc *camera, t_cvc *d, t_objects *o, double t_min)
{
	t_cvc	v[2];
	t_cvc	p;
	t_cvc	t[2];
	double	dot;

	v[0] = v_new(*o->c2, *o->c1, '-');
	v[1] = v_new(*o->c3, *o->c1, '-');
	p = cross(*d, v[1]);
	dot = v_scalar(v[0], p);
	if (fabs(dot) < t_min)
		return (-1);
	dot = 1 / dot;
	t[0] = v_new(*camera, *o->c1, '-');
	t[1].y = v_scalar(t[0], p) * dot;
	if (t[1].y < 0 || t[1].y > 1)
		return (-1);
	t[0] = cross(t[0], v[0]);
	t[1].z = v_scalar(*d, t[0]) * dot;
	if (t[1].z < 0 || t[1].y + t[1].z > 1)
		return (-1);
	return ((t[1].x = v_scalar(v[1], t[0]) * dot) >= t_min ? t[1].x : -1);
}

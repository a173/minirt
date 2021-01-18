/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 21:34:17 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/21 21:34:18 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		cpy_x(t_copy *to, t_objects *from, double x)
{
	to->id = from->id;
	to->rgb = (t_cvc) {from->rgb->x, from->rgb->y, from->rgb->z};
	to->calc = x;
	to->nv = (t_cvc) {from->nv->x, from->nv->y, from->nv->z};
}

static t_copy	closest(t_cvc *camera, t_cvc *d, t_all *a, double m)
{
	double		c;
	double		x;
	t_objects	*o;
	t_copy		s;

	c = INT_MAX;
	m == 0.01 ? c : (c = 1);
	o = a->object;
	s.calc = -1;
	while (o)
	{
		if (o->id == 2 && (x = sphere(camera, d, o, m)) != -1 && x <= c)
			cpy_x(&s, o, (c = x));
		else if (o->id == 3 && (x = plane(camera, d, o, m)) != -1 && x <= c)
			cpy_x(&s, o, (c = x));
		else if (o->id == 4 && (x = square(camera, d, o, m)) != -1 && x <= c)
			cpy_x(&s, o, (c = x));
		else if (o->id == 5 && (x = cylinder(camera, d, o, m)) != -1 && x <= c)
			cpy_x(&s, o, (c = x));
		else if (o->id == 6 && (x = triangle(camera, d, o, m)) != -1 && x <= c)
			cpy_x(&s, o, (c = x));
		o = o->next;
	}
	return (s);
}

static void		add_color(t_cvc *rgb, t_cvc *l, t_cvc *p, t_objects *s)
{
	double dot;
	double temp;

	if ((dot = v_scalar(*p, *l)) > 0)
	{
		temp = s->d * dot / (v_len(*p) * v_len(*l));
		rgb->x += temp * (s->rgb->x / 255);
		rgb->y += temp * (s->rgb->y / 255);
		rgb->z += temp * (s->rgb->z / 255);
	}
}

static t_cvc	lighting(t_cvc *p, t_cvc *n, t_all *a)
{
	t_cvc		t[4];
	t_objects	*s;
	t_copy		shadow;

	t[0] = (t_cvc) {a->light, a->light, a->light};
	s = a->object;
	while (s)
	{
		t[3] = *n;
		if (s->id == 1)
		{
			t[1] = v_new(*s->c1, *p, '-');
			t[2] = v_scalar(*n, v_new(*a->camera->c, *p, '-')) < 0 ?
				v_new(*p, v_num(n, -0.00009, '*'), '+') :
					v_new(*p, v_num(n, 0.00009, '*'), '+');
			shadow = closest(&t[2], &t[1], a, 0.00001);
			t[3] = v_scalar(t[3], t[1]) < 0 ? v_num(n, -1, '*') : t[3];
			shadow.calc == -1 ? add_color(&t[0], &t[1], &t[3], s) : 0;
		}
		s = s->next;
	}
	return (t[0]);
}

t_cvc			traceray(t_camera *camera, t_cvc d, t_all *a)
{
	t_copy	s;
	t_cvc	p;

	s = closest(camera->c, &d, a, 0.01);
	if (s.calc == -1)
		return (s.rgb = (t_cvc) {a->rgb->x * a->light,
			a->rgb->y * a->light, a->rgb->z * a->light});
		p = v_new(*camera->c, v_num(&d, s.calc, '*'), '+');
	s.id == 2 ? s.nv = v_new(p, s.nv, '-') : s.nv;
	s.id == 2 ? s.nv = v_num(&s.nv, v_len(s.nv), '/') : s.nv;
	return ((s.rgb = v_new(s.rgb, lighting(&p, &s.nv, a), '*')));
}

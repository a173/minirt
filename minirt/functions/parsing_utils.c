/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 20:53:15 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/21 20:53:16 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int				skip(char *l, int *i)
{
	while ((l[*i] > 8 && l[*i] < 14) || l[*i] == 32)
		(*i)++;
	return (1);
}

int				next(int n, int *i)
{
	if ((*i += n) && !n)
		return (0);
	return (1);
}

int				v_o(t_objects *o)
{
	if (o->nv->x < -1 || o->nv->x > 1 || o->nv->y < -1 ||
		o->nv->y > 1 || o->nv->z < -1 || o->nv->z > 1)
		return (0);
	return (1);
}

t_cvc			*nv(t_objects o)
{
	t_cvc	c;
	double	s;

	c.x = o.c1->y * o.c3->z - o.c2->y * o.c3->z - o.c1->y * o.c2->z -
		o.c1->z * o.c3->y + o.c2->z * o.c3->y + o.c1->z * o.c2->y;
	c.y = o.c1->z * o.c3->x - o.c2->z * o.c3->x - o.c1->z * o.c2->x -
		o.c1->z * o.c3->z + o.c2->x * o.c3->z + o.c1->x * o.c2->z;
	c.z = o.c1->x * o.c3->y - o.c2->x * o.c3->y - o.c1->x * o.c2->y -
		o.c1->y * o.c3->x + o.c2->y * o.c3->x + o.c1->y * o.c2->x;
	s = sqrt(c.x * c.x + c.y * c.y + c.z * c.z);
	return (new_cvc(c.x / s, c.y / s, c.z / s));
}

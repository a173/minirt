/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 21:00:09 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/21 21:00:10 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cvc	v_new(t_cvc v1, t_cvc v2, char c)
{
	t_cvc n;

	if (c == '+')
		n = (t_cvc) {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
	else if (c == '-')
		n = (t_cvc) {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
	else
		n = (t_cvc) {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
	return (n);
}

double	v_scalar(t_cvc v1, t_cvc v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	v_len(t_cvc v)
{
	return (sqrt(v_scalar(v, v)));
}

t_cvc	v_num(t_cvc *v, double n, char c)
{
	t_cvc x;

	if (c == '*')
		x = (t_cvc) {v->x * n, v->y * n, v->z * n};
	else
		x = (t_cvc) {v->x / n, v->y / n, v->z / n};
	return (x);
}

void	cpy_vector(t_cvc *to, t_cvc *from)
{
	to->x = from->x;
	to->y = from->y;
	to->z = from->z;
}

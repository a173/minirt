/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 21:37:30 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/21 21:37:32 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	f_obj(t_objects *object)
{
	void *temp;

	if (!object)
		return (0);
	while (object)
	{
		free(object->c1);
		free(object->c2);
		free(object->c3);
		free(object->rgb);
		free(object->nv);
		temp = object->next;
		free(object);
		object = temp;
	}
	return (0);
}

static int	f_cam(t_all *all)
{
	void *temp;

	while (all->c_cam && all->camera)
	{
		free(all->camera->c);
		free(all->camera->v);
		temp = all->camera->next;
		free(all->camera);
		all->camera = temp;
		all->c_cam--;
	}
	return (0);
}

int			is_free(t_all *all)
{
	if (!all)
		return (0);
	free(all->rgb);
	f_obj(all->object);
	f_cam(all);
	free(all);
	return (0);
}

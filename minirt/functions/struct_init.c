/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 21:35:39 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/21 21:35:40 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_all		*init_all(void)
{
	t_all *temp;

	if (!(temp = (t_all*)malloc(sizeof(t_all))) && !error_logs(-1))
		return (NULL);
	temp->x = -1;
	temp->y = -1;
	temp->light = -1;
	temp->save = 0;
	temp->rgb = NULL;
	temp->camera = NULL;
	temp->c_cam = 0;
	temp->object = NULL;
	return (temp);
}

t_objects	*init_object(int i)
{
	t_objects *temp;

	if (!(temp = (t_objects*)malloc(sizeof(t_objects))))
		return (NULL);
	temp->id = i;
	temp->c1 = NULL;
	temp->c2 = NULL;
	temp->c3 = NULL;
	temp->rgb = NULL;
	temp->d = -1;
	temp->h = -1;
	temp->nv = NULL;
	temp->next = NULL;
	return (temp);
}

t_camera	*init_camera(void)
{
	t_camera *temp;

	if (!(temp = (t_camera*)malloc(sizeof(t_camera))))
		return (NULL);
	temp->c = NULL;
	temp->v = NULL;
	temp->g = -1;
	temp->prev = NULL;
	temp->next = NULL;
	return (temp);
}

t_camera	*add_camera_back(t_camera **lst, t_camera *new)
{
	t_camera *temp;

	if (!(*lst))
	{
		if (!new)
			return (NULL);
		*lst = new;
	}
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		temp->next->prev = temp;
	}
	return (new);
}

t_objects	*add_object_back(t_objects **lst, t_objects *new)
{
	t_objects *temp;

	if (!(*lst))
	{
		if (!new)
			return (NULL);
		*lst = new;
	}
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	return (new);
}

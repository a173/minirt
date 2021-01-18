/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 20:55:57 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/21 20:55:58 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"

static void	while_cam(t_all *all)
{
	t_camera *start;
	t_camera *next;

	start = all->camera;
	next = all->camera;
	while (next->next)
		next = next->next;
	start->prev = next;
	next->next = start;
}

static int	validator(t_all *all)
{
	if ((all->x == -1 || all->y == -1 || all->light == -1
		|| !all->rgb || !all->camera) && !error_logs(0))
		return (0);
	while_cam(all);
	return (1);
}

int			navigator(t_all *a, char *line, int i)
{
	if (skip(line, &i) && *line == '\0')
		return (1);
	else if (!ft_strncmp("#", &line[i], 1))
		return (1);
	else if (!ft_strncmp("R", &line[i], 1))
		return (write_scr(a, &line[i], 1));
	else if (!ft_strncmp("A", &line[i], 1))
		return (write_amb(a, &line[i], 1));
	else if (!ft_strncmp("c", &line[i], 1) && ft_strncmp("cy", &line[i], 2))
		return (write_camera(a, &line[i], 1));
	else if (!ft_strncmp("l", &line[i], 1))
		return (write_light(a, &line[i], 1));
	else if (!ft_strncmp("sp", &line[i], 2))
		return (write_sphere(a, &line[i], 2));
	else if (!ft_strncmp("pl", &line[i], 2))
		return (write_plane(a, &line[i], 2));
	else if (!ft_strncmp("sq", &line[i], 2))
		return (write_square(a, &line[i], 2));
	else if (!ft_strncmp("cy", &line[i], 2))
		return (write_cylinder(a, &line[i], 2));
	else if (!ft_strncmp("tr", &line[i], 2))
		return (write_triangle(a, &line[i], 2));
	return (0);
}

t_all		*parser(int fd)
{
	int		ret;
	char	*line;
	t_all	*all;

	if (!(all = init_all()))
		return (NULL);
	while ((ret = get_next_line(fd, &line) > 0))
	{
		if (!if_clear(all, &line, &ret))
			return (NULL);
		free(line);
	}
	if ((ret < 0 && !error_logs(-4) && !is_free(all))
		|| !if_clear(all, &line, &ret))
		return (NULL);
	free(line);
	if (!validator(all))
		return (NULL);
	close(fd);
	return (all);
}

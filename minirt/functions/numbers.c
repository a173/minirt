/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 21:38:55 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/21 21:38:56 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cvc	*new_cvc(double x, double y, double z)
{
	t_cvc *cvc;

	if (!(cvc = malloc(sizeof(t_cvc))))
		return (NULL);
	cvc->x = x;
	cvc->y = y;
	cvc->z = z;
	return (cvc);
}

int		ft_atoi(char *line, int *nb)
{
	int		i;
	long	n;

	i = 0;
	n = 0;
	if (line[i] == '-')
		i++;
	while (line[i] && line[i] >= 48 && line[i] <= 57)
		n = 10 * n + (line[i++] - 48);
	if (i == 0 || (line[0] == '-' && i == 1))
		return (0);
	if ((line[0] == '-' && i > 11) || (line[0] != '-' && i > 10))
		return (0);
	if (n > INT_MAX || n < INT_MIN)
		return (0);
	*nb = (line[0] == '-') ? -n : n;
	return (i);
}

int		ft_atoc(char *line, t_cvc **c)
{
	int i;
	int r;
	int n;
	int color[3];

	i = 0;
	n = -1;
	while (++n < 3)
	{
		if (!(r = ft_atoi(&line[i], &color[n])) || r > 3)
			return (0);
		if (color[n] < 0 || color[n] > 255)
			return (0);
		i += r;
		if (n < 2 && line[i] != ',')
			return (0);
		else if (n < 2 && line[i] == ',')
			i++;
	}
	if (!(*c = new_cvc(color[0], color[1], color[2])))
		return (0);
	return (i);
}

int		ft_atof(char *line, double *nb)
{
	int		i;
	int		n;
	double	s;

	if (!(i = ft_atoi(line, &n)))
		return (0);
	*nb = n;
	if (line[i] == '.')
		i++;
	s = 1;
	while (line[i] && line[i] >= 48 && line[i] <= 57)
		*nb += (line[i++] - 48) / (s *= 10);
	line[0] == '-' && *nb > 0 && *nb < 1 ? *nb = -(*nb) : *nb;
	return (i);
}

int		ft_atov(char *line, t_cvc **vc)
{
	int		i;
	int		r;
	int		n;
	double	v[3];

	i = 0;
	n = -1;
	while (++n < 3)
	{
		if (!(r = ft_atof(&line[i], &v[n])))
			return (0);
		i += r;
		if (n < 2 && line[i] != ',')
			return (0);
		else if (n < 2 && line[i] == ',')
			i++;
	}
	if (!(*vc = new_cvc(v[0], v[1], v[2])))
		return (0);
	return (i);
}

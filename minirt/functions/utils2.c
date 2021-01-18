/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 21:48:17 by acaryn            #+#    #+#             */
/*   Updated: 2020/12/21 21:48:18 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = -1;
	s1 = (unsigned char*)str1;
	s2 = (unsigned char*)str2;
	while (++i < n && (s1[i] || s2[i]))
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (0);
}

int		error_logs(int error)
{
	if (error == -4)
		write(STDERR_FILENO, "Error read file\n", 16);
	else if (error == -6)
		write(STDERR_FILENO, "File creation error\n", 20);
	else if (error == -5)
		write(STDERR_FILENO, "Invalid arguments\n", 18);
	else if (error == -3)
		write(STDERR_FILENO, "Invalid number of arguments\n", 28);
	else if (error == -2)
		write(STDERR_FILENO, "Invalid file name\n", 18);
	else if (error == -1)
		write(STDERR_FILENO, "Memory error\n", 13);
	else if (error == 0)
		write(STDERR_FILENO, "Invalid config file\n", 20);
	return (0);
}

int		ft_isdigit(int c)
{
	return (c > 47 && c < 58);
}

t_cvc	cross(t_cvc a, t_cvc b)
{
	return ((t_cvc) {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x});
}

int		if_clear(t_all *a, char **line, int *ret)
{
	if (!(*ret = navigator(a, *line, 0)) || *ret < 0)
	{
		error_logs(*ret) && is_free(a);
		free(*line);
		return (0);
	}
	return (1);
}

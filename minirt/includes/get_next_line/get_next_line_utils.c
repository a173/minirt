/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:59:01 by acaryn            #+#    #+#             */
/*   Updated: 2020/11/09 13:00:04 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

char		*ft_strchr(const char *str, int ch)
{
	int	i;
	int	n;

	i = -1;
	n = ft_strlen(str);
	while (n >= ++i)
		if (str[i] == ch)
			return ((char*)(str) + i);
	return (NULL);
}

char		*ft_strcpy(char *dest, char *src)
{
	int i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

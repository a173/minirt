/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:32:01 by acaryn            #+#    #+#             */
/*   Updated: 2020/11/09 20:49:36 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strdup(const char *str)
{
	char	*s;
	int		i;

	i = -1;
	if ((s = malloc((ft_strlen(str) + 1) * sizeof(char))) != NULL)
	{
		while (str[++i])
			s[i] = str[i];
		s[i] = '\0';
	}
	return (s);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!(str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
	{
		str[i] = s2[j];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*check_str(char *str, char **line)
{
	char	*n;
	int		i;

	i = -1;
	n = NULL;
	*line = ft_strdup("");
	if (str)
	{
		if ((n = ft_strchr(str, '\n')))
		{
			*n = '\0';
			free(*line);
			*line = ft_strdup(str);
			ft_strcpy(str, ++n);
		}
		else
		{
			free(*line);
			*line = ft_strdup(str);
			while (str[++i])
				*str = '\0';
		}
	}
	return (n);
}

static void	check_buf(char **buf, char **n, char *str, char **line)
{
	char	*tmp;

	if ((*n = ft_strchr(*buf, '\n')))
	{
		**n = '\0';
		*n += 1;
		str = ft_strcpy(str, *n);
	}
	tmp = ft_strjoin(*line, *buf);
	free(*line);
	*line = tmp;
}

int			get_next_line(int fd, char **line)
{
	ssize_t		b_read;
	char		*buf;
	char		*n;
	static char	str[1024][BUFFER_SIZE + 1];

	buf = NULL;
	if (BUFFER_SIZE < 1 || fd < 0 || fd > 1024 ||
		read(fd, buf, 0) < 0 || !(line))
		return (-1);
	if (!(n = check_str(str[fd], line)))
	{
		if (!(*line) || !(buf = malloc((BUFFER_SIZE + 1) * sizeof(char))))
			return (-1);
		while (!n && (b_read = read(fd, buf, BUFFER_SIZE)) > 0)
		{
			buf[b_read] = '\0';
			check_buf(&buf, &n, &str[fd][0], line);
		}
		free(buf);
		return ((b_read || ft_strlen(str[fd])) ? 1 : 0);
	}
	return (1);
}

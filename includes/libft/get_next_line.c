/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lutomasz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 20:11:16 by lutomasz          #+#    #+#             */
/*   Updated: 2019/01/25 14:37:26 by lutomasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

char	*free_str(char *to_free, char *tmp)
{
	if (to_free != NULL && tmp != NULL)
	{
		free(to_free);
		to_free = tmp;
	}
	return (to_free);
}

int		fill_line(int fd, char **line, char **s, int ret)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((s[fd][i] != '\n' && s[fd][i] != '\0') && s[fd][i])
		i++;
	if (s[fd][i] == '\n')
	{
		if (!(*line = ft_strsub(s[fd], 0, i)))
			return (-1);
		if (!(tmp = ft_strsub(s[fd], i + 1, (ft_strlen(s[fd])))))
			return (-1);
		s[fd] = free_str(s[fd], tmp);
		s[fd][0] == '\0' ? ft_strdel(&s[fd]) : 0;
	}
	else if (s[fd][i] == '\0')
	{
		if (ret == BUFF_SIZE)
			get_next_line(fd, line);
		if (!(*line = ft_strdup(s[fd])))
			return (-1);
		ft_strdel(&s[fd]);
	}
	return (1);
}

int		fill_rest(int fd, char **line, char **s, char *buf)
{
	int		i;
	char	*tmp;
	int		ret;

	i = 0;
	while ((s[fd][i] != '\n' && s[fd][i] != '\0') && s[fd][i])
		i++;
	if (s[fd][i] == '\n')
	{
		if (!(*line = ft_strsub(s[fd], 0, i)))
			return (-1);
		if (!(tmp = ft_strsub(s[fd], i + 1, (ft_strlen(s[fd])))))
			return (-1);
		s[fd] = free_str(s[fd], tmp);
		s[fd][0] == '\0' ? ft_strdel(&s[fd]) : 0;
	}
	else if (s[fd][i] == '\0')
	{
		ret = read(fd, buf, BUFF_SIZE);
		ret == BUFF_SIZE ? get_next_line(fd, line) : 0;
		if (!(*line = ft_strdup(s[fd])))
			return (-1);
		ft_strdel(&s[fd]);
	}
	return (1);
}

int		ft_read(int fd, char **line, char **s, char *buf)
{
	int		ret;
	char	*tmp;

	if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (s[fd] == NULL)
		{
			if (!(s[fd] = ft_strdup(buf)))
				return (-1);
			if (!(ft_strchr(buf, '\n')))
				return (ft_read(fd, line, s, buf));
		}
		else
		{
			if (!(tmp = ft_strjoin(s[fd], buf)))
				return (-1);
			s[fd] = free_str(s[fd], tmp);
			if (!(ft_strchr(buf, '\n')))
				return (ft_read(fd, line, s, buf));
		}
	}
	return (ret);
}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	static char	*s[OPEN_MAX];
	char		*buf;

	ret = 1;
	if (fd < 0 || line == NULL || !(buf = ft_strnew(BUFF_SIZE + 1))
		|| BUFF_SIZE <= 0 || fd > OPEN_MAX)
		return (-1);
	if (s[fd] != NULL && ft_strchr(s[fd], '\n'))
	{
		fill_rest(fd, line, s, buf);
		ft_strdel(&buf);
		return (1);
	}
	else
	{
		ret = ft_read(fd, line, s, buf);
		ft_strdel(&buf);
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (s[fd] == NULL || s[fd][0] == '\0'))
		return (0);
	return (fill_line(fd, line, s, ret));
}

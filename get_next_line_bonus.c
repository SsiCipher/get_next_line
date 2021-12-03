/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanab <yanab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 12:26:07 by yanab             #+#    #+#             */
/*   Updated: 2021/12/03 21:52:00 by yanab            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char *str)
{
	char	*line;
	int		line_length;

	if (!str)
		return (NULL);
	line_length = 0;
	while (str[line_length] && str[line_length] != '\n')
		line_length++;
	if (str[line_length] == '\n')
		line_length += 1;
	if (line_length == 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (line_length + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, str, line_length);
	line[line_length] = '\0';
	return (line);
}

char	*extract_rest(char *str)
{
	int		rest_length;
	char	*rest;

	if (!str)
		return (NULL);
	while (*str != '\0' && *str != '\n')
		str++;
	if (*str == '\n')
		str++;
	rest_length = ft_strlen(str);
	if (rest_length == 0)
		return (NULL);
	rest = (char *)malloc(sizeof(char) * (rest_length + 1));
	if (!rest)
		return (NULL);
	ft_memcpy(rest, str, rest_length);
	rest[rest_length] = '\0';
	return (rest);
}

int	fill_buff(int fd, char **rest)
{
	int			read_bytes;
	char		*buff;
	char		*tmp;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	read_bytes = read(fd, buff, BUFFER_SIZE);
	if (read_bytes == -1)
		return (0);
	while (read_bytes > 0)
	{
		buff[read_bytes] = '\0';
		tmp = rest[fd];
		rest[fd] = join_strs(rest[fd], buff);
		free(tmp);
		if (has_nl(rest[fd]))
			break ;
		read_bytes = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (1);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	char		*line;
	int			error;
	static char	*rest[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	error = fill_buff(fd, rest);
	if (!error)
		return (NULL);
	line = extract_line(rest[fd]);
	tmp = rest[fd];
	rest[fd] = extract_rest(rest[fd]);
	free(tmp);
	return (line);
}

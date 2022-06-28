/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdavos <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:41:36 by sdavos            #+#    #+#             */
/*   Updated: 2022/01/07 17:41:39 by sdavos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_l(char *mem, int i, char *str)
{
	while (mem[i] && mem[i] != '\n')
	{
		str[i] = mem[i];
		i++;
	}
	if (mem[i] == '\n')
	{
		str[i] = mem[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_line(char *mem, char *buff)
{
	int		i;
	char	*str;

	i = 0;
	free(buff);
	if (!mem[i])
		return (NULL);
	while (mem[i] && mem[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	return (get_l(mem, i, str));
}

char	*new_line(char *mem)
{
	int		i;
	int		j;
	char	*str;
	int		len;

	i = 0;
	len = ft_strlen_gnl(mem);
	while (mem[i] && mem[i] != '\n')
		i++;
	if (!mem[i])
	{
		free(mem);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (len - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (mem[i])
		str[j++] = mem[i++];
	str[j] = '\0';
	free(mem);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*mem;
	char		*buff;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes = 1;
	while ((bytes != 0) && (!ft_strchr_gnl(mem, '\n')))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		mem = ft_strjoin_gnl(mem, buff);
	}
	line = get_line(mem, buff);
	mem = new_line(mem);
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guantino <guantino@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:20:34 by guantino          #+#    #+#             */
/*   Updated: 2025/11/28 18:10:04 by guantino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>

static char	*read_to_buff(int fd, char *buff)
{
	char	*tmp;
	int		r;

	tmp = (char *)malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	if (!buff)
	{
		buff = (char *)malloc(1);
		if (!buff)
			return (free(tmp), NULL);
		buff[0] = '\0';
	}
	r = 1;
	while (r > 0 && !ft_strchr(buff, '\n'))
	{
		r = read(fd, tmp, BUFFER_SIZE);
		if (r < 0)
			return (free(tmp), free(buff), NULL);
		if (r == 0)
			break ;
		tmp[r] = '\0';
		buff = gnl_strjoin(buff, tmp);
		if (!buff)
			return (free(tmp), NULL);
	}
	free(tmp);
	return (buff);
}

static char	*extract_line(char *buff)
{
	int		i;
	char	*line;

	if (!buff || !buff[0])
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	i++;
	line = ft_substr(buff, 0, i);
	return (line);
}

static char	*save_remainder(char *buff)
{
	int		i;
	char	*new_buff;

	if (!buff)
		return (NULL);
	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	i++;
	new_buff = ft_substr(buff, i, ft_strlen(buff) - i);
	free(buff);
	return (new_buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = read_to_buff(fd, buff);
	if (!buff)
		return (NULL);
	line = extract_line(buff);
	buff = save_remainder(buff);
	return (line);
}
/*
int main (int argc, char **argv)
{
	int fd = open (argv[1], O_RDONLY);
	char *line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		line = get_next_line(fd);
	}
	close(fd);
}
*/

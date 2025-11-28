/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guantino <guantino@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:20:34 by guantino          #+#    #+#             */
/*   Updated: 2025/11/28 13:02:36 by guantino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>

static int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*ft_strchr(const char *buf, int c)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == (unsigned char)c)
			return ((char *)(buf + i));
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(buf + i));
	return ((void *)0);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	sub_len;
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (NULL);
	sub_len = slen - start;
	if (sub_len > len)
		sub_len = len;
	new = (char *)malloc(sub_len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < sub_len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char	*gnl_strjoin(char *s1, char *s2)
{
	char	*new;
	int		len1;
	int		len2;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = (char *)malloc(len1 + len2 + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}

static char	*read_to_buff(int fd, char *buff)
{
	char	*tmp;
	int		r;

	tmp = (char *)malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	r = 1;
	while (r > 0 && !ft_strchr(buff, '\n'))
	{
		r = read(fd, tmp, BUFFER_SIZE);
		if (r < 0)
		{
			free(tmp);
			free(buff);
			return (NULL);
		}
		if (r == 0)
			break ;
		tmp[r] = '\0';
		buff = gnl_strjoin(buff, tmp);
		if (!buff)
		{
			free(tmp);
			return (NULL);
		}
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
	if (buff[i] == '\n')
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

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = read_to_buff(fd, buff);
	if (!buff)
		return (NULL);
	line = extract_line(buff);
	buff = save_remainder(buff);
	return (line);
}

int main(int argc, char **argv)
{
	(void)argc;
	int fd = open(argv[1], O_RDONLY);
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
}

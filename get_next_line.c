/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guantino <guantino@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:20:34 by guantino          #+#    #+#             */
/*   Updated: 2025/11/14 18:21:04 by guantino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *buf, int c)
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

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*new;

	if (!s1)
	{
		s1 = malloc(sizeof (char));
		s1[0] = 0;
	}
	if (!s1 || !s2)
		return (NULL);
	i = 0;
	new = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		new[i] = s1[i];
		i++;
	}
	while (i < (ft_strlen(s1) + ft_strlen(s2)))
	{
		new[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	if (s1)
		free(s1);
	new[i] = '\0';
	return (new);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
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

char	*get_next_line(int fd)
{
	char	*buff;
	char	*aux;
	int	r;
	int	i;
	
	r = 0;
	aux = malloc((BUFFER_SIZE + 1) * sizeof(char));
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	i = 0;
	while((r += read(fd, buff, BUFFER_SIZE)) && !ft_strchr(buff, '\n'))
	{
		if (r == -1)
		{
			free(buff);
			free(aux);
			return (NULL);
		}
		aux[r] = 0;
		aux = ft_strjoin(aux, buff);
	}
	while(buff[i] && buff[i] != '\n')
		i++;
	aux = ft_strjoin(aux, ft_substr(buff, 0, i));
	return (aux);
}

int main(int argc, char **argv)
{
	(void)argc;
	int fd = open(argv[1], O_RDONLY);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		size1;
	int		size2;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	new = (char *) malloc((size1 + size2) * sizeof(char));
	while (i < size1)
	{
		new[i] = s1[i];
		i++;
	}
	while (i < (size1 + size2))
	{
		new[i] = s2[i - size1];
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
	
	aux = malloc((BUFFER_SIZE + 1) * sizeof(char));
	i = 0;
	while((r = read(fd, buff, BUFFER_SIZE)) && !ft_strchr(buff, '\n'))
	{
		if (r == -1)
		{
			free(buff);
			free(aux);
			return (NULL);
		}
		aux[r] = '\0';
		aux = ft_strjoin(aux, buff);
	}
	return (aux);
}

int main(int argc, char **argv)
{
	int fd = open(argv[1], O_RDONLY);
	printf("%s", get_next_line(fd));
}

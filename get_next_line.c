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
	if (!new)
		return (NULL);
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
	return (new);
}

char	*get_next_line(int fd)
{
	int	buff_size;
	int	i;
	char	*c;
	char	*line;
	
	buff_size = BUFFER_SIZE;
	c = malloc(buff_size * sizeof(char));
	line = malloc(buff_size * sizeof(char));
	i = 0;
	if (!line)
		return (NULL);
	while (read(fd, c, buff_size))
	{
		write(1, c, buff_size);
		i++;
	}
	return (line);
}

int main(int argc, char **argv)
{
	(void)argc;
	int fd = open(argv[1], O_RDONLY);
	printf("%s", get_next_line(fd));
}

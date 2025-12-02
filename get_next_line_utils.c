/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guantino <guantino@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:21:29 by guantino          #+#    #+#             */
/*   Updated: 2025/11/28 18:02:43 by guantino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

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

static char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*str;

	len = ft_strlen(s);
	i = 0;
	if (len == 0)
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = 0;
		return (str);
	}
	str = (char *) malloc(len * sizeof(char) + sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	return (str);
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
		return (ft_strdup(""));
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

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*new;
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
	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guantino <guantino@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:21:29 by guantino          #+#    #+#             */
/*   Updated: 2025/11/14 18:21:40 by guantino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*get_next_line(int fd)
{
	char	*mem;
	int		buf_size;
	int		i;

	i = 0;
	buf_size = def_buf_size;
	mem = ft_malloc_line(buf_size + 1);
	while (c != '\n')
	{
		if (read(fd, &c, 1) <= 0)
		{
			free(mem);
			return (NULL);
		}
		mem[i] = c;
		if (i >= buf_size)
		{
			mem = ft_remalloc_line(mem, buf_size + 1,
					buf_size + def_buf_size + 1);
			buf_size += 5;
		}
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

void	*ft_memset(char *s, char c, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		s[i] = c;
		i++;
	}
	return (s);
}

void	*ft_memcpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	*ft_malloc_line(int size)
{
	char	*str;

	str = malloc(size);
	ft_memset(str, '|', size);
	return (str);
}

char	*ft_remalloc_line(char *mem, int old_size, int size)
{
	char	*aux_mem;

	aux_mem = ft_malloc_line(size);
	ft_memcpy(aux_mem, mem, old_size);
	free(mem);
	return (aux_mem);
}

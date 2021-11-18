/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedrole <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:03:11 by mpedrole          #+#    #+#             */
/*   Updated: 2021/11/17 15:03:12 by mpedrole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

size_t	ft_strlen(const char *str)
{
	int	size;

	size = 0;
	while (str[size] != '\0')
	{
		size += 1;
	}
	return (size);
}



char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(*str) * size + 1);
	if (str == NULL)
		return (NULL);
	while (i <= size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	if (s == NULL)
		return (NULL);
	subs = ft_strnew(len);
	if (subs == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		subs[i] = s[start + i];
		i++;
	}
	return (subs);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	size = 0;
	while (s1[size])
		size += 1;
	str = (char*)malloc(sizeof(*str) * size + 1);
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i] = s1[i];
		i++;
	}
	str[size] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char*)s);
		s++;
	}
	if (*s == c)
		return ((char*)s);
	return (NULL);
}

void	ft_memdel(void **ap)
{
	if (ap != NULL)
	{
		free(*ap);
		*ap = NULL;
	}
}

void	ft_strdel(char **as)
{
	if (as != NULL && *as != NULL)
		ft_memdel((void**)as);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i += 1;
	}
	dst[i] = src[i];
	return (dst);
}

char	*ft_strcat(char *dst, const char *src)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		strlen;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	strlen = ft_strlen(s1) + ft_strlen(s2);
	str = ft_strnew(strlen);
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	return (str);
}


static char	*appendline(char **s)
{
	int		len;
	char	*tmp;
	char	*line;

	len = 0;
	while ((*s)[len] != '\n' && (*s)[len] != '\0')
		len++;
	if ((*s)[len] == '\n')
	{
		line = ft_strsub(*s, 0, len + 1);
		tmp = ft_strdup(&((*s)[len + 1]));
		free(*s);
		*s = tmp;
		if ((*s)[0] == '\0')
			ft_strdel(s);
	}
	else
	{
		line = ft_strdup(*s);
		ft_strdel(s);
	}
	return (line);
}

static char	*output(char **s, int ret, int fd)
{
	if (ret < 0)
		return (NULL);
	else if (ret == 0 && s[fd] == NULL)
		return (NULL);
	else
		return (appendline(&s[fd]));
}

char	*get_next_line(int fd)
{
	int			ret;
	static char	*s[4096];
	char		buff[BUFFER_SIZE + 1];
	char		*tmp;

	if (fd < 0)
		return (NULL);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(s[fd], buff);
			free(s[fd]);
			s[fd] = tmp;
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
	}
	return (output(s, ret, fd));
}

/*int main()
{
	int	fd;

	fd = open("f", 0);
	printf("1. /%s\\\n", get_next_line(fd));
	printf("2. /%s\\\n", get_next_line(fd));
	printf("3. /%s\\\n", get_next_line(fd));
	printf("4. /%s\\\n", get_next_line(fd));
	printf("5. /%s\\\n", get_next_line(fd));
	printf("6. /%s\\\n", get_next_line(fd));
	printf("7. /%s\\\n", get_next_line(fd));
	printf("8. /%s\\\n", get_next_line(fd));
	printf("9. /%s\\\n", get_next_line(fd));
	printf("10. /%s\\\n", get_next_line(fd));
	printf("11. /%s\\\n", get_next_line(fd));
	close(fd);
}*/

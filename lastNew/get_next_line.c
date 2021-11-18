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
#define BUFFER_SIZE 1
#endif

size_t ft_strlen(const char *str)
{
	int size;

	size = 0;
	while (str[size] != '\0')
	{
		size += 1;
	}
	return (size);
}

char *ft_calloc(size_t size)
{
	char *str;
	size_t i;

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

char *ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *subs;
	size_t i;

	if (s == NULL)
		return (NULL);
	subs = ft_calloc(len);
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

char *ft_strdup(const char *s1)
{
	int i;
	int size;
	char *str;

	i = 0;
	size = 0;
	while (s1[size])
		size += 1;
	str = (char *)malloc(sizeof(*str) * size + 1);
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

char	*search_or_del(char **str, int c)
{
	int	i;

	i = 0;
	if (c > 0)
	{
		while ((*str)[i++])
		{
			if ((*str)[i] == c)
				return ((char *)*str);
		}
		if ((*str)[++i] == c)
			return ((char *)*str);
		return (NULL);
	}
	if (str != NULL && *str != NULL)
	{
		if (str != NULL)
		{
		free(*str);
		*str = NULL;
		}
	}
	return (NULL);
}

char *ft_strcpy(char *dst, const char *src)
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

char *ft_strjoin(char const *s1, char const *s2)
{
	int strlen;
	char *str;

	if (!s1 || !s2)
		return (NULL);
	strlen = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc(strlen);
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcpy(str + ft_strlen(s1), s2);
	return (str);
}

static char *get_line(char **s)
{
	int len;
	char *tmp;
	char *line;

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
			search_or_del(s, -1);
	}
	else
	{
		line = ft_strdup(*s);
		search_or_del(s, -1);
	}
	return (line);
}

static char *format_output(char **s, int ret)
{
	if (ret < 0)
		return (NULL);
	else if (ret == 0 && *s == NULL)
		return (NULL);
	else
	{
		return (get_line(s));
	}
}

char *get_next_line(int fd)
{
	int ret;
	static char *s;
	char buff[BUFFER_SIZE + 1];
	char *tmp;
	char *debg;

	if (fd < 0)
		return (NULL);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (s == NULL)
			s = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(s, buff);
			free(s);
			s = tmp;
		}
		if (search_or_del(&s, '\n'))
			break;
	}
	debg = s;
	printf("\n\ndebug : %s\n\n", s);
	return (format_output(&s, ret));
}

int main()
{
	int fd;

	fd = open("alternate_line_nl_with_nl", 0);
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
}

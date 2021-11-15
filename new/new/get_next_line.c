#include "get_next_line.h"
//#define BUFFER_SIZE 1

int	ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	int				i;
	char			*d;
	const char		*s;

	d = (char *)dest;
	s = (const char *)src;
	i = (int)n;
	if (d == NULL && s == NULL)
		return (NULL);
	while (i > 0)
	{
		*d++ = *s++;
		i--;
	}
	return (dest);
}

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	unsigned int	len;

	len = (unsigned int)ft_strlen((char *)src);
	if (len + 1 < size)
		ft_memcpy(dest, src, len + 1);
	else if (size != 0)
	{
		ft_memcpy(dest, src, size - 1);
		dest[size - 1] = '\0';
	}
	//free(src);
	return (len);
}

char	*ft_strdup(char *src, int free_needed)
{
	char	*ptr;
	int		len;

	len = ft_strlen(src);
	ptr = (char *) malloc (len + 1);
	if (ptr != NULL)
		ft_strlcpy(ptr, src, len + 1);
	else
		return (NULL);
	if (free_needed == 1)
		free(src);
	return (ptr);
}

// Function modified, so this function may be the cause of some problems
char	*ft_strjoin(char *a, char *b)
{
	char	*r;
	int		len;

	if (!a)
		return (NULL);
	if (a && b)
	{
		len = ft_strlen(a) + ft_strlen(b);
		r = malloc(sizeof(char) * (len + 1));
		if (r == NULL)
			return (NULL);
		ft_strlcpy(r, a, ft_strlen(a) + 1);
		ft_strlcpy(r + ft_strlen(a), b, ft_strlen(b) + 1);
		//printf("r is %c (%i)\n", r[2], (int)r[2]);
		free(a);
		//free(b);
		return (r);
	}
	else
		return (NULL);
}

/* This function's going to check if a new line is already on the buffer and if it's true, that's going to return the new line and stock the rest on the static var buf */
char	*chck_nl(char **buf, int endfile)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = -42;
	//printf("buff 2 is %c (%i)\n", (*buf)[2], (int)(*buf)[2]);
	while ((*buf)[i] != '\0')
	{
		if ((*buf)[i] == '\n')
			j = i;
		i++;
	}
	if (endfile)
		j = i;
	if (j == -42)
		return (NULL);
	res = malloc(sizeof(char) * (j + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i <= j)
	{
		res[i] = (*buf)[i];
		i++;
	}
	res[i] = '\0';
	*buf = ft_strdup(*buf + (j + 1), 1);
	return (res);
}

int	chck_endfile(char **buf)
{
	int	i;

	i = 0;
	while (i <= BUFFER_SIZE)
	{
		if ((*buf)[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

/* This function's going to read a file while no new line is on the buffer, return the new line and add the surplus into the static var buf */
char	*rd_file(char **buf, int fd, int endfile)
{
	char	*res;
	char	*tmp;

	tmp = ft_strdup(*buf, 0);
	while (read(fd, *buf, BUFFER_SIZE) > 0)
	{
		if (chck_endfile(buf))
			endfile = 1;
		//Verifier si le buf contient un \0 si c'est le cas faire une action special
		tmp = ft_strjoin(tmp, *buf);
		//printf("tmp is %c (%i)\n", tmp[2], (int)tmp[2]);
		res = chck_nl(&tmp, endfile);
		if (res)
		{
			*buf = ft_strdup(tmp, 0);
			free(tmp);
			return (res);
		}
	}
	free(tmp);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	static int	endfile;
	char		*res;

	if (buf)
	{
		res = chck_nl(&buf, endfile);
		if (!res)
		{
			res = rd_file(&buf, fd, endfile);
			if (!buf)
				free(buf);
		}
	}
	else
	{
		endfile = 0;
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		res = rd_file(&buf, fd, endfile);
	}
	if (endfile && !res)
	{
		free(buf);
	}

	return (res);
}

/*int main()
{
	int	fd;

	fd = open("41_nos_nl", 0);
	printf("1. /%s\\\n", get_next_line(fd));
	printf("2. /%s\\\n", get_next_line(fd));
	close(fd);
	return (NULL);
}*/

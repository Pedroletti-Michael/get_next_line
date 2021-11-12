/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedrole <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:06:59 by mpedrole          #+#    #+#             */
/*   Updated: 2021/11/02 17:07:01 by mpedrole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#define BUFFER_SIZE 42

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}



char	*strjoin_style(char *a, char *b)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(a) + ft_strlen(b) - 1));
	if (!res)
		return (NULL);
	while (*a != '\0')
		res[i++] = *a++;
	while (*b != '\0')
		res[i++] = *b++;
	res[i] = '\0';
	//free(a);
	return (res);
}

int	chck_nwln(char *a)
{
	int	i;

	i = 0;
	while (a[i] != '\0')
	{
		if (a[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*sep_str(char *a, int x)
{
	char	*res;
	int		size;
	int		i;
	int		nwln;
	int		j;

	nwln = 0;
	i = 0;
	size = 0;
	if (x == 0)
	{
		while (a[i] != '\n')
			i++;
		res = malloc(sizeof(char) * i + 1);
		i = 0;
		if (!res)
			return (NULL);
		while (a[i] != '\n')
		{
			res[i] = a[i];
			i++;
		}
		res[i++] = '\n';
		res[i] = '\0';
		return (res);
	}
	while (a[i] != '\0')
	{
		if (nwln == 1)
			size++;
		else if (a[i] == '\n')
		{
			nwln = 1;
			j = i + 1;
		}
		i++;
	}
	res = malloc(sizeof(char) * size + 1);
	if (!res)
		return (NULL);
	i = 0;
	size = 0;
	while (a[j] != '\0')
		res[size++] = a[j++];
	res[size] = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	char			*buf;
	static char		*chr;
	char			*res;
	int				i;
	int				read_res;

	read_res = 1;
	i = 0;
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	res = malloc(sizeof(char) * 1);
	res[0] = '\0';
	buf[0] = '\0';
	if (!chr)
	{
		chr = malloc(sizeof(char) * 1);
		chr[0] = '\0';
	}
	while((read_res = read(fd, buf, BUFFER_SIZE)) && i == 0 && read_res > 0)
	{
		chr = strjoin_style(chr, buf);
		if (chck_nwln(chr))
			i = 1;
	}
	//Trouver un moyen de changer la priorité des actions ou alors faire en sorte de rajouter un check afin de verifier si il reste du contenu dans le buffer ou dans le chr
	if ((read_res == 0 || read_res == -1) && i == 0)
	{
		free(chr);
		free(buf);
		free(res);
		return (NULL);
	}
	chr = strjoin_style(chr, buf);
	res = sep_str(chr, 0);
	chr = sep_str(chr, 1);
	free(buf);
	return(res);
}

int main()
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
}

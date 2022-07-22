/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:33:04 by asoler            #+#    #+#             */
/*   Updated: 2022/07/06 02:44:38 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/libft.h"

char	*strcat_result(char	*dest, char	*src)
{
	int		total;
	char	*result;
	int		l_dest;
	int		i;

	i = 0;
	l_dest = gnl_strlen(dest);
	total = l_dest + gnl_strlen(src);
	result = malloc(total * sizeof(char) + 1);
	while (total)
	{
		while (i < l_dest)
		{
			result[i] = dest[i];
			i++;
			total--;
		}
		result[i] = *src;
		i++;
		src++;
		total--;
	}
	result[i] = 0;
	free(dest);
	return (result);
}

int	invalid_read(char **result, char *buf, int x)
{
	if ((x < 0 || x > BUFFER_SIZE) || !x)
	{
		if (!*result[0])
		{
			free(*result);
			*result = 0;
		}
		free(buf);
		return (1);
	}
	return (0);
}

void	save_remains(char **aux, char *result, char *buf, int remains)
{
	if (*aux)
		ft_strcpy(*aux, (*aux + ft_strlen(result)));
	else
	{
		*aux = malloc(sizeof(char) * (remains));
		ft_strcpy(*aux, buf);
	}
}

int	add_remains_to_result(char **aux, char **result)
{
	int	remains;

	if (*aux)
	{
		remains = count_remains_lf(*aux, ft_strlen(*aux));
		*result = strcat_result(*result, *aux);
		if (!remains)
		{
			free(*aux);
			*aux = 0;
		}
	}
	else
		remains = 0;
	return (remains);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*aux;
	char		*result;
	int			remains;
	int			x;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	result = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	*result = 0;
	remains = add_remains_to_result(&aux, &result);
	while (!remains)
	{
		x = read(fd, buf, BUFFER_SIZE);
		if (invalid_read(&result, buf, x))
			return (result);
		buf[x] = 0;
		remains = count_remains_lf(buf, x);
		result = strcat_result(result, buf);
	}
	save_remains(&aux, result, (buf + (x - remains + 1)), remains);
	free(buf);
	return (result);
}

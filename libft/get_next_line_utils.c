/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 02:46:48 by asoler            #+#    #+#             */
/*   Updated: 2022/07/06 02:44:53 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_remains_lf(char *s, int size)
{
	while (*s != '\n' && size)
	{
		s++;
		size--;
	}
	return (size);
}

int	gnl_strlen(char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		i++;
		if (*s == '\n')
			return (i);
		s++;
	}
	return (i);
}

void	ft_strcpy(char *dest, char *src)
{
	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = 0;
}

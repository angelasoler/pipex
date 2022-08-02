/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:24:25 by asoler            #+#    #+#             */
/*   Updated: 2022/08/02 21:16:07 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	chr_cmp(const char	*s, char c)
{
	while (*s)
	{
		if (c == *s)
			return (0);
		else
			s++;
	}
	return (1);
}

char	*ft_strtrim(char *s1, char const *set)
{
	int		i;
	int		beg;
	int		mark;
	char	*result;

	mark = 0;
	i = 0;
	while (mark != 1)
	{
		mark = chr_cmp(set, s1[i]);
		i++;
	}
	beg = i - 1 ;
	i = ft_strlen(s1) - 1;
	mark = 0;
	while (mark != 1)
	{
		mark = chr_cmp(set, s1[i]);
		i--;
	}
	i++;
	result = ft_substr(s1, beg, ((i - beg) + 1));
	free(s1);
	return (result);
}

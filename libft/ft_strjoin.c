/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:26:52 by asoler            #+#    #+#             */
/*   Updated: 2022/08/04 23:06:49 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char			*result;
	unsigned int	i;
	unsigned int	i2;
	unsigned int	size;

	size = ft_strlen(s1) + ft_strlen(s2);
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (0);
	i = 0;
	i2 = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[i2])
	{
		result[i] = s2[i2];
		i++;
		i2++;
	}
	result[i] = s2[i2];
	return (result);
}

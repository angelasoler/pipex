/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:21:29 by asoler            #+#    #+#             */
/*   Updated: 2022/08/01 14:48:28 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	wait_and_free(pid_t pid, char **cmd)
{
	if (waitpid(pid, 0, 0) < 0)
	{
		ft_printf("Wait fail %s\n", strerror(errno));
		return (0);
	}
	free_array(cmd);
	return (1);
}

int	verify_access(char *path, int mode, int ret)
{
	if (access(path, mode) < 0)
	{
		ft_printf("bash: %s: %s\n", path, strerror(errno));
		ret = 1;
		return (0);
	}
	ret = 0;
	return (1);
}

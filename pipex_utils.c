/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:21:29 by asoler            #+#    #+#             */
/*   Updated: 2022/08/03 19:40:35 by asoler           ###   ########.fr       */
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

int	wait_and_free(pid_t pid, char **cmd, int *status, int *ret)
{
	if (waitpid(pid, status, 0) < 0)
	{
		ft_printf("Wait fail %s\n", strerror(errno));
		return (0);
	}
	free_array(cmd);
	if (WIFEXITED(*status))
		*ret = WEXITSTATUS(*status);
	return (1);
}

int	verify_access(char *path, int mode)
{
	if (access(path, mode) < 0)
	{
		ft_printf("bash: %s: %s\n", path, strerror(errno));
		return (0);
	}
	return (1);
}

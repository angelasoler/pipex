/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:21:29 by asoler            #+#    #+#             */
/*   Updated: 2022/08/05 19:37:30 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	size_t	len;
	char	*path;
	char	*result;
	int		i;

	i = 0;
	len = ft_strlen(envp[i]);
	path = ft_strnstr(envp[i], "PATH", len);
	while (!path)
	{
		i++;
		len = ft_strlen(envp[i]);
		path = ft_strnstr(envp[i], "PATH", len);
	}
	result = ft_strdup(&path[5]);
	return (result);
}

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

void	free_crowd(char **vector, char *s)
{
	free_array(vector);
	free(s);
}

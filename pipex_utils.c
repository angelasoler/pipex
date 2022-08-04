/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:21:29 by asoler            #+#    #+#             */
/*   Updated: 2022/08/04 19:16:59 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	size_t	len;
	char	*path;
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
	return (path);
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

int	verify_access(char *path, int mode)
{
	if (access(path, mode) < 0)
	{
		ft_printf("bash: %s: command not found\n", path);
		return (0);
	}
	return (1);
}

int	verify_command(char **cmd, t_args *args, int *pid)
{
	if (!verify_access(cmd[0], F_OK))
	{
		*pid = -1;
		if (cmd[0][0] != '\0')
			free_array(cmd);
		else
		{
			free(cmd[0]);
			free(cmd);
		}
		args->proc.ret = 127;
		return (127);
	}
	return (0);
}

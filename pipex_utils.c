/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:21:29 by asoler            #+#    #+#             */
/*   Updated: 2022/08/04 23:04:14 by asoler           ###   ########.fr       */
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

int	verify_access(char *path, int mode)
{
	if (access(path, mode) < 0)
	{
		if (mode == R_OK)
			ft_printf("some message\n");
		return (0);
	}
	return (1);
}

int	verify_path(char **cmd, t_args *args)
{
	char	*path;
	char	**tr_path;
	char	*aux;
	int		i;

	i = 0;
	path = find_path(args->envp);
	tr_path = ft_split(path, ':');
	free(path);
	aux = ft_strdup(&cmd[0][8]);
	path = ft_strjoin(tr_path[i], aux);
	while (tr_path[i] && !verify_access(path, F_OK))
	{
		free(path);
		i++;
		if (!tr_path[i])
		{
			free(aux);
			free_array(tr_path);
			return (1);
		}
		else
			path = ft_strjoin(tr_path[i], aux);
	}
	free(*cmd);
	*cmd = ft_strdup(path);
	free(aux);
	free(path);
	free_array(tr_path);
	return (0);
}

int	verify_command(char **cmd, t_args *args, int *pid)
{
	if (!verify_access(cmd[0], F_OK))
	{
		if (cmd[0][0] != '\0' && !verify_path(&cmd[0], args))
		{
			return (0);
		}
		ft_printf("bash: %s: command not found\n", cmd[0]);
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

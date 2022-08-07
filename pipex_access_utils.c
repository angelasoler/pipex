/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_access_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 16:08:56 by asoler            #+#    #+#             */
/*   Updated: 2022/08/07 18:54:35 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	verify_access(char *path, int mode)
{
	if (access(path, mode) < 0)
	{
		if (mode == R_OK || mode == W_OK)
			ft_printf("bash: %s: %s\n", path, strerror(errno));
		return (0);
	}
	return (1);
}

int	verify_path(char **cmd, t_args *args)
{
	t_path	path;

	path.i = 0;
	path.path = find_path(args->envp);
	path.tr_path = ft_split(path.path, ':');
	free(path.path);
	path.aux = ft_strdup(&cmd[0][8]);
	path.path = ft_strjoin(path.tr_path[path.i], path.aux);
	while (path.tr_path[path.i] && !verify_access(path.path, F_OK))
	{
		free(path.path);
		path.i++;
		if (!path.tr_path[path.i])
		{
			free_crowd(path.tr_path, path.aux);
			return (1);
		}
		else
			path.path = ft_strjoin(path.tr_path[path.i], path.aux);
	}
	free(*cmd);
	*cmd = ft_strdup(path.path);
	free_crowd(path.tr_path, path.aux);
	free(path.path);
	return (0);
}

int	verify_command(char **cmd, t_args *args, int *pid)
{
	if (!verify_access(cmd[0], F_OK))
	{
		if (cmd[0][0] != '\0' && !verify_path(&cmd[0], args))
			return (0);
		if (cmd[0][0] != '\0')
			ft_printf("bash: %s: command not found\n", &cmd[0][9]);
		else
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

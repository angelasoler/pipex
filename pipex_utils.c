/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:21:29 by asoler            #+#    #+#             */
/*   Updated: 2022/07/27 20:48:44 by asoler           ###   ########.fr       */
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

void	initialize_cmds_args(t_data *data)
{
	data->cmd1 = ft_split(data->argv[2], ' ');
	data->cmd2 = ft_split(data->argv[3], ' ');
	data->cmd1[0] = ft_strjoin("/usr/bin/", data->cmd1[0]);
	data->cmd2[0] = ft_strjoin("/usr/bin/", data->cmd2[0]);
	data->file_fd = open(data->argv[1], O_RDONLY);
}

int	wait_and_free(pid_t pid, char **cmd)
{
	if (waitpid(pid, 0, 0) < 0)
	{
		ft_printf("Wait fail");
		return (0);
	}
	free_array(cmd);
	return (1);
}

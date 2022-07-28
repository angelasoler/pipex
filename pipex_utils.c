/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:21:29 by asoler            #+#    #+#             */
/*   Updated: 2022/07/28 15:09:49 by asoler           ###   ########.fr       */
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

void	initialize_cmds_args(t_args *args)
{
	args->file_fd = open(args->argv[1], O_RDONLY);
	if (args->file_fd == -1)
	{
		ft_printf("Error\n%s\n", strerror(errno));
		exit (0);
	}
	args->cmd1 = ft_split(args->argv[2], ' ');
	args->cmd2 = ft_split(args->argv[3], ' ');
	args->cmd1[0] = ft_strjoin("/usr/bin/", args->cmd1[0]);
	args->cmd2[0] = ft_strjoin("/usr/bin/", args->cmd2[0]);
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

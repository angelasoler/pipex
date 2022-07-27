/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:14:54 by asoler            #+#    #+#             */
/*   Updated: 2022/07/27 02:23:48 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initialize_cmds_args(t_data *data)
{
	data->cmd1 = ft_split(data->argv[2], ' ');
	data->cmd2 = ft_split(data->argv[3], ' ');
	data->cmd1[0] = ft_strjoin("/usr/bin/", data->cmd1[0]);
	data->cmd2[0] = ft_strjoin("/usr/bin/", data->cmd2[0]);
}

int	initialize_files_descriptor(t_data *data)
{
	data->file_fd = open(data->argv[1], O_RDONLY);
	if (pipe(data->pipe_fd) < 0)
		return (0);
	data->pid = fork();
	if (data->pid < 0)
		return (0);
	return (1);
}

void	parent_process(t_data *data)
{
	close(data->pipe_fd[1]);
	wait(NULL);
	free_array(data->cmd1);
	data->file_fd = open(data->argv[4], O_RDWR | O_CREAT | O_TRUNC);
	dup2(data->pipe_fd[0], 0);
	close(data->pipe_fd[0]);
	dup2(data->file_fd, 1);
	close(data->file_fd);
}

int	handle_processes(t_data *data)
{
	if (!initialize_files_descriptor(data))
	{
		ft_printf("Pipe or fork");
		return (0);
	}
	if (!data->pid)
	{
		close(data->pipe_fd[0]);
		dup2(data->file_fd, 0);
		close(data->file_fd);
		dup2(data->pipe_fd[1], 1);
		if (execve(data->cmd1[0], data->cmd1, NULL) < 0)
		{
			ft_printf("Execve fail");
			return (0);
		}
	}
	parent_process(data);
	if (execve(data->cmd2[0], data->cmd2, NULL) < 0)
	{
		ft_printf("Execve fail");
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 5)
	{
		ft_printf("Wrong arguments number");
		return (-1);
	}
	data.argv = argv;
	initialize_cmds_args(&data);
	if (!handle_processes(&data))
	{
		ft_printf("Something went wrong with processes");
		return (-1);
	}
}

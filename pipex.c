/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:14:54 by asoler            #+#    #+#             */
/*   Updated: 2022/07/27 14:50:29 by asoler           ###   ########.fr       */
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

int	initialize_pipe_and_process(t_data *data)
{
	data->file_fd = open(data->argv[1], O_RDONLY);
	if (pipe(data->pipe_fd) < 0)
		return (0);
	data->pid = fork();
	if (data->pid < 0)
		return (0);
	return (1);
}

int	cmd2_process(t_data *data)
{
	data->file_fd = open(data->argv[4], O_RDWR | O_CREAT | O_TRUNC);
	data->pid2 = fork();
	if (data->pid < 0)
		return (0);
	return (1);
}

int	handle_processes(t_data *data)
{
	if (!initialize_pipe_and_process(data))
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
		close(data->pipe_fd[1]);
		if (execve(data->cmd1[0], data->cmd1, NULL) < 0)
		{
			ft_printf("Execve fail");
			return (0);
		}
	}
	close(data->pipe_fd[1]);
	waitpid(data->pid, 0, 0);
	free_array(data->cmd1);
	dup2(data->pipe_fd[0], 0);
	close(data->pipe_fd[0]);
	if (!cmd2_process(data))
		return (0);
	if (!data->pid2)
	{
		dup2(data->file_fd, 1);
		close(data->file_fd);
		if (execve(data->cmd2[0], data->cmd2, NULL) < 0)
		{
			ft_printf("Execve2 fail");
			return (0);
		}
	}
	waitpid(data->pid2, 0, 0);
	free_array(data->cmd2);
	close(data->file_fd);
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
	return (argc);
}

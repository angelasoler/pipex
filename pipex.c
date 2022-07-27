/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:14:54 by asoler            #+#    #+#             */
/*   Updated: 2022/07/28 00:31:05 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_cmd1(t_data *data)
{
	if (pipe(data->pipe_fd) < 0)
		return (0);
	data->pid_in = fork();
	if (data->pid_in < 0)
		return (0);
	return (1);
}

int	fork_cmd2(t_data *data)
{
	data->file_fd = open(data->argv[4], O_RDWR | O_CREAT | O_TRUNC);
	data->pid_out = fork();
	if (data->pid_out < 0)
		return (0);
	return (1);
}

int	exec_cmds(int output_fd, char **cmd)
{
	dup2(output_fd, 1);
	close(output_fd);
	if (execve(cmd[0], cmd, NULL) < 0)
	{
		perror("Execve fail");
		return (0);
	}
	return (1);
}

int	handle_processes(t_data *data)
{
	if (!data->pid_in)
	{
		close(data->pipe_fd[0]);
		dup2(data->file_fd, 0);
		close(data->file_fd);
		if (exec_cmds(data->pipe_fd[1], data->cmd1))
			return (0);
	}
	close(data->pipe_fd[1]);
	if (!wait_and_free(data->pid_in, data->cmd1))
		return (0);
	dup2(data->pipe_fd[0], 0);
	close(data->pipe_fd[0]);
	if (!fork_cmd2(data))
		return (0);
	if (!data->pid_out)
	{
		if (!exec_cmds(data->file_fd, data->cmd2))
			return (0);
	}
	if (!wait_and_free(data->pid_out, data->cmd2))
		return (0);
	close(data->file_fd);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 5)
	{
		ft_printf("Error: %s\n", strerror(EINVAL));
		return (-1);
	}
	data.argv = argv;
	initialize_cmds_args(&data);
	if (!fork_cmd1(&data) || !handle_processes(&data))
	{
		perror("Something went wrong with processes");
		return (10);
	}
	return (-6);
}

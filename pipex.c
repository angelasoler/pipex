/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:14:54 by asoler            #+#    #+#             */
/*   Updated: 2022/07/27 19:54:32 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	initialize_args(t_data *data)
{
	data->cmd1 = ft_split(data->argv[2], ' ');
	data->cmd2 = ft_split(data->argv[3], ' ');
	data->cmd1[0] = ft_strjoin("/usr/bin/", data->cmd1[0]);
	data->cmd2[0] = ft_strjoin("/usr/bin/", data->cmd2[0]);
	data->file_fd = open(data->argv[1], O_RDONLY);
	if (pipe(data->pipe_fd) < 0)
		return (0);
	return (1);
}

int	fork_cmd(pid_t pid)
{
	pid = fork();
	if (pid < 0)
	{
		ft_printf("Fork");
		return (0);
	}
	return (1);
}

int	exec_cmds(int output_fd, char **cmd)
{
	dup2(output_fd, 1);
	close(output_fd);
	if (execve(cmd[0], cmd, NULL) < 0)
	{
		ft_printf("Execve fail");
		return (0);
	}
	return (1);
}

int	handle_processes(t_data *data)
{
	if (!initialize_args(data) || !fork_cmd(data->pid))
		return (0);


	if (!data->pid)
	{
		close(data->pipe_fd[0]);
		dup2(data->file_fd, 0);
		close(data->file_fd);
		if (exec_cmds(data->pipe_fd[1], data->cmd1))
			return (0);
	}
	
	close(data->pipe_fd[1]);
	
	waitpid(data->pid, 0, 0);
	free_array(data->cmd1);
	data->file_fd2 = open(data->argv[4], O_RDWR | O_CREAT | O_TRUNC);
	
	dup2(data->pipe_fd[0], 0);
	close(data->pipe_fd[0]);

	if (!fork_cmd(data->pid2))
		return (0);
	if (!data->pid2)
	{
		if (!exec_cmds(data->file_fd2, data->cmd2))
			return (0);
	}
	
	waitpid(data->pid2, 0, 0);
	free_array(data->cmd2);
	
	close(data->file_fd2);
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
	if (!handle_processes(&data))
	{
		ft_printf("Something went wrong with processes");
		return (-1);
	}
	return (argc);
}

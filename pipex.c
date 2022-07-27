/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:14:54 by asoler            #+#    #+#             */
/*   Updated: 2022/07/28 00:48:32 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_cmd1(t_args *args)
{
	if (pipe(args->proc.pipe_fd) < 0)
		return (0);
	args->proc.pid_in = fork();
	if (args->proc.pid_in < 0)
		return (0);
	return (1);
}

int	fork_cmd2(t_args *args)
{
	args->file_fd = open(args->argv[4], O_RDWR | O_CREAT | O_TRUNC);
	args->proc.pid_out = fork();
	if (args->proc.pid_out < 0)
		return (0);
	return (1);
}

int	exec_cmds(int output_fd, char **cmd, char **envp)
{
	dup2(output_fd, 1);
	close(output_fd);
	if (execve(cmd[0], cmd, envp) < 0)
	{
		perror("Execve fail");
		return (0);
	}
	return (1);
}

int	handle_processes(t_args *args)
{
	if (!args->proc.pid_in)
	{
		close(args->proc.pipe_fd[0]);
		dup2(args->file_fd, 0);
		close(args->file_fd);
		if (exec_cmds(args->proc.pipe_fd[1], args->cmd1, args->envp))
			return (0);
	}
	close(args->proc.pipe_fd[1]);
	if (!wait_and_free(args->proc.pid_in, args->cmd1))
		return (0);
	dup2(args->proc.pipe_fd[0], 0);
	close(args->proc.pipe_fd[0]);
	if (!fork_cmd2(args))
		return (0);
	if (!args->proc.pid_out)
	{
		if (!exec_cmds(args->file_fd, args->cmd2, args->envp))
			return (0);
	}
	if (!wait_and_free(args->proc.pid_out, args->cmd2))
		return (0);
	close(args->file_fd);
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_args	args;

	if (argc != 5)
	{
		ft_printf("Error: %s\n", strerror(EINVAL));
		return (-1);
	}
	args.argv = argv;
	args.envp = envp;
	initialize_cmds_args(&args);
	if (!fork_cmd1(&args) || !handle_processes(&args))
	{
		perror("Something went wrong with processes");
		return (10);
	}
	return (20);
}

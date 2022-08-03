/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:14:54 by asoler            #+#    #+#             */
/*   Updated: 2022/08/03 20:21:47 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_cmd1(t_args *args)
{
	if (!verify_access(args->argv[1], R_OK))
	{
		args->proc.pid_in = -1;
		return (1);
	}
	args->file_fd = open(args->argv[1], O_RDONLY);
	alloc_exec_paths(args->argv[2], &args->cmd1);
	if (!verify_access(args->cmd1[0], F_OK))
	{
		args->proc.pid_in = -1;
		close(args->file_fd);
		if (args->cmd1[0][0] != '\0')
			free_array(args->cmd1);
		else
		{
			free(args->cmd1[0]);
			free(args->cmd1);
		}
		args->proc.ret = 127;
		return (127);
	}
	args->proc.pid_in = fork();
	if (args->proc.pid_in < 0)
		return (1);
	return (0);
}

int	fork_cmd2(t_args *args)
{
	args->file_fd = open(args->argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!verify_access(args->argv[4], W_OK))
	{
		args->proc.pid_out = -1;
		args->proc.ret = 1;
		return (1);
	}
	alloc_exec_paths(args->argv[3], &args->cmd2);
	if (!verify_access(args->cmd2[0], F_OK))
	{
		args->proc.pid_out = -1;
		if (args->cmd2[0][0])
			free_array(args->cmd2);
		else
		{
			free(args->cmd2[0]);
			free(args->cmd2);
		}
		args->proc.ret = 127;
		return (127);
	}
	args->proc.pid_out = fork();
	if (args->proc.pid_out < 0)
		return (1);
	return (0);
}

void	exec_cmds(int output_fd, char **cmd, char **envp)
{
	if (dup2(output_fd, 1) < 0)
		ft_printf("bash: %s: %s\n", strerror(errno));
	close(output_fd);
	execve(cmd[0], cmd, envp);
	perror("Execve fail");
	free_array(cmd);
	exit(EXIT_FAILURE);
}

int	handle_processes(t_args *args)
{
	if (pipe(args->proc.pipe_fd) < 0)
		exit(EXIT_FAILURE);
	if (!fork_cmd1(args) && !args->proc.pid_in)
	{
		close(args->proc.pipe_fd[0]);
		dup2(args->file_fd, 0);
		close(args->file_fd);
		exec_cmds(args->proc.pipe_fd[1], args->cmd1, args->envp);
	}
	close(args->proc.pipe_fd[1]);
	if (args->proc.pid_in != -1)
		wait_and_free(args->proc.pid_in, args->cmd1, \
		&args->proc.status, &args->proc.ret);
	dup2(args->proc.pipe_fd[0], 0);
	close(args->proc.pipe_fd[0]);
	if (!fork_cmd2(args) && !args->proc.pid_out)
		exec_cmds(args->file_fd, args->cmd2, args->envp);
	if (args->proc.pid_out != -1)
		wait_and_free(args->proc.pid_out, args->cmd2, \
		&args->proc.status, &args->proc.ret);
	close(args->file_fd);
	return (0);
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
	handle_processes(&args);
	return (args.proc.ret);
}

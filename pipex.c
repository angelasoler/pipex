/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:14:54 by asoler            #+#    #+#             */
/*   Updated: 2022/07/28 21:58:51 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_cmd1(t_args *args)
{
	if (!verify_access(args->argv[1], R_OK))
		return (0);
	args->file_fd = open(args->argv[1], O_RDONLY);
	args->cmd1 = ft_split(args->argv[2], ' ');
	args->cmd1[0] = ft_strjoin("/usr/bin/", args->cmd1[0]);
	if (pipe(args->proc.pipe_fd) < 0)
		return (0);
	args->proc.pid_in = fork();
	if (args->proc.pid_in < 0)
		return (0);
	return (1);
}

int	fork_cmd2(t_args *args)
{
	args->file_fd = open(args->argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!verify_access(args->argv[4], W_OK))
		return (0);
	args->cmd2 = ft_split(args->argv[3], ' ');
	args->cmd2[0] = ft_strjoin("/usr/bin/", args->cmd2[0]);
	args->proc.pid_out = fork();
	if (args->proc.pid_out < 0)
		return (0);
	return (1);
}

void	exec_cmds(int output_fd, char **cmd, char **envp)
{
	dup2(output_fd, 1);
	close(output_fd);
	execve(cmd[0], cmd, envp);
	perror("Execve fail");
	free_array(cmd);
	exit(EXIT_FAILURE);
}

int	handle_processes(t_args *args)
{
	if (!args->proc.pid_in)
	{
		close(args->proc.pipe_fd[0]);
		dup2(args->file_fd, 0);
		close(args->file_fd);
		exec_cmds(args->proc.pipe_fd[1], args->cmd1, args->envp);
	}
	close(args->proc.pipe_fd[1]);
	if (!wait_and_free(args->proc.pid_in, args->cmd1))
		return (0);
	dup2(args->proc.pipe_fd[0], 0);
	close(args->proc.pipe_fd[0]);
	if (!fork_cmd2(args))
		return (0);
	if (!args->proc.pid_out)
		exec_cmds(args->file_fd, args->cmd2, args->envp);
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
	if (!fork_cmd1(&args) || !handle_processes(&args))
		perror("Something went wrong");
	return (0);
}

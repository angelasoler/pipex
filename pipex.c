/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:14:54 by asoler            #+#    #+#             */
/*   Updated: 2022/07/26 14:04:34 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while(array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	main(int argc, char *argv[])
{
	char	**split_args;
	pid_t	pid;
	int		file_fd;
	int		pipe_fd1[2];
	// int		pipe_fd2[2];
	split_args = ft_split(argv[2], ' ');
	split_args[0] = ft_strjoin("/usr/bin/", split_args[0]);

	file_fd = open(argv[1], O_RDONLY); //input
	if (pipe(pipe_fd1) == -1)
		return (-1);
	// if (pipe(pipe_fd2) == -1)
	// 	return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
	{
		close(pipe_fd1[1]);
		// close(pipe_fd2[0]);
		dup2(file_fd, 0);
		close(file_fd);
		// dup2(file_fdxxxx, 1);
		close(pipe_fd1[0]);
		execve(split_args[0], split_args, NULL);
	}
	else
	{

		close(pipe_fd1[0]);
		// close(pipe_fd1[0]);
		// close(pipe_fd2[1]);
		dup2(pipe_fd1[1], 1);
		wait(NULL);
		free_array(split_args);
		// close(pipe_fd1[1]);
		exit (0);
	}
	// file_fd = open(argv[1], O_CREAT); //output
	return (argc);
}

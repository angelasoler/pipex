/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:14:54 by asoler            #+#    #+#             */
/*   Updated: 2022/07/26 21:50:50 by asoler           ###   ########.fr       */
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
	char	**split_args2;
	pid_t	pid;
	int		file_fd;
	int		pipe_fd1[2];
	split_args = ft_split(argv[2], ' ');
	split_args[0] = ft_strjoin("/usr/bin/", split_args[0]);
	split_args2 = ft_split(argv[3], ' ');
	split_args2[0] = ft_strjoin("/usr/bin/", split_args2[0]);

	file_fd = open(argv[1], O_RDONLY);
	if (pipe(pipe_fd1) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
	{
		close(pipe_fd1[0]);
		dup2(file_fd, 0);
		close(file_fd);
		dup2(pipe_fd1[1], 1);
		if (execve(split_args[0], split_args, NULL) == -1)
			return (-1);
	}
	else
	{
		close(pipe_fd1[1]);
		wait(NULL);
		free_array(split_args);
		file_fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC);
		dup2(pipe_fd1[0], 0);
		close(pipe_fd1[0]);
		dup2(file_fd, 1);
		if (execve(split_args2[0], split_args2, NULL) == -1)
			return (-1);
	}
	return (argc);
}

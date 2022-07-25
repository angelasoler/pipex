/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:14:54 by asoler            #+#    #+#             */
/*   Updated: 2022/07/25 22:43:35 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_org(char *s1, char const *s2)
{
	char			*result;
	unsigned int	i;
	unsigned int	size;

	size = ft_strlen(s1) + ft_strlen(s2);
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (0);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		result[i] = *s2;
		s2++;
		i++;
	}
	result[i] = *s2;
	return (result);
}

int	main(int argc, char *argv[])
{
	char	**split_args;
	pid_t	pid;
	int		file_fd;
	int		pipe_fd1[2];
	// int		pipe_fd2[2];
	split_args = ft_split(argv[2], ' ');
	split_args[0] = ft_strjoin_org("/usr/bin/", split_args[0]);

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
		// close(pipe_fd1[1]);
		exit (0);
	}
	// file_fd = open(argv[1], O_CREAT); //output
	return (argc);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:14:54 by asoler            #+#    #+#             */
/*   Updated: 2022/07/26 14:38:40 by asoler           ###   ########.fr       */
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
	split_args = ft_split(argv[2], ' ');
	split_args[0] = ft_strjoin("/usr/bin/", split_args[0]);

	file_fd = open(argv[1], O_RDONLY);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (!pid)
	{
		dup2(file_fd, 0);
		close(file_fd);
		execve(split_args[0], split_args, NULL);
	}
	else
	{
		wait(NULL);
		free_array(split_args);
		exit (0);
	}
	return (argc);
}

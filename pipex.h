/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:37:46 by asoler            #+#    #+#             */
/*   Updated: 2022/07/28 00:19:50 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# include "includes/libft.h"
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# define PIPEX_H

typedef struct s_data
{
	char	**argv;
	char	**cmd1;
	char	**cmd2;
	pid_t	pid_in;
	pid_t	pid_out;
	int		file_fd;
	int		pipe_fd[2];
}	t_data;

void	free_array(char **array);
int		wait_and_free(pid_t pid, char **cmd);
void	initialize_cmds_args(t_data *data);

#endif
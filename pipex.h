/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:37:46 by asoler            #+#    #+#             */
/*   Updated: 2022/07/27 19:33:31 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# include "includes/libft.h"
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# define PIPEX_H

typedef struct s_data
{
	char	**argv;
	char	**cmd1;
	char	**cmd2;
	pid_t	pid;
	pid_t	pid2;
	int		file_fd;
	int		file_fd2;
	int		pipe_fd[2];
}	t_data;

void	free_array(char **array);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:37:46 by asoler            #+#    #+#             */
/*   Updated: 2022/07/27 02:22:02 by asoler           ###   ########.fr       */
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
	int		pipe_fd[2];
	int		file_fd;
}	t_data;

void	free_array(char **array);

#endif
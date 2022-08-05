/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 21:37:46 by asoler            #+#    #+#             */
/*   Updated: 2022/08/05 19:41:44 by asoler           ###   ########.fr       */
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

typedef struct s_path
{
	char	*path;
	char	**tr_path;
	char	*aux;
	int		i;
}	t_path;

typedef struct s_proc
{
	pid_t	pid_in;
	pid_t	pid_out;
	int		pipe_fd[2];
	int		status;
	int		ret;
}	t_proc;

typedef struct s_args
{
	char	**argv;
	char	**cmd1;
	char	**cmd2;
	char	**envp;
	char	*path;
	int		file_fd;
	t_proc	proc;
}	t_args;

void	free_array(char **array);
int		wait_and_free(pid_t pid, char **cmd, int *status, int *ret);
int		verify_access(char *path, int mode);
int		alloc_exec_paths(char *path, char ***cmd);
char	*find_path(char **envp);
int		verify_command(char **cmd, t_args *args, int *pid);
void	free_crowd(char **vector, char *s);

#endif
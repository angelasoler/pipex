/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 02:21:29 by asoler            #+#    #+#             */
/*   Updated: 2022/08/02 01:05:58 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	wait_and_free(pid_t pid, char **cmd, int *status)
{
	if (waitpid(pid, status, 0) < 0)
	{
		ft_printf("Wait fail %s\n", strerror(errno));
		return (0);
	}
	free_array(cmd);
	return (1);
}

int	verify_access(char *path, int mode)
{
	if (access(path, mode) < 0)
	{
		ft_printf("bash: %s: %s\n", path, strerror(errno));
		return (0);
	}
	return (1);
}

void	alloc_exec_paths(char *path, char ***cmd)
{
	if (*path == 0)
	{
		*cmd = malloc(sizeof(char *) * 2);
		*cmd[0] = ft_strdup("/usr/bin/dxfsdf");
	}
	else
	{
		*cmd = ft_split(path, ' ');
		*cmd[0] = ft_strjoin("/usr/bin/", *cmd[0]);
	}
}

// ==2032== Memcheck, a memory error detector
// ==2032== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
// ==2032== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
// ==2032== Command: ./pipex hello   newfile
// ==2032== 
// bash: /usr/bin/dxfsdf: No such file or directory
// ==2032== Conditional jump or move depends on uninitialised value(s)
// ==2032==    at 0x401720: free_array (in /home/coder/projetos_fase1/pipex/pipex)
// ==2032==    by 0x4012B8: fork_cmd1 (in /home/coder/projetos_fase1/pipex/pipex)
// ==2032==    by 0x4014E8: handle_processes (in /home/coder/projetos_fase1/pipex/pipex)
// ==2032==    by 0x4016E6: main (in /home/coder/projetos_fase1/pipex/pipex)
// ==2032== 
// bash: /usr/bin/dxfsdf: No such file or directory
// ==2032== Conditional jump or move depends on uninitialised value(s)
// ==2032==    at 0x401720: free_array (in /home/coder/projetos_fase1/pipex/pipex)
// ==2032==    by 0x4013CB: fork_cmd2 (in /home/coder/projetos_fase1/pipex/pipex)
// ==2032==    by 0x4015CD: handle_processes (in /home/coder/projetos_fase1/pipex/pipex)
// ==2032==    by 0x4016E6: main (in /home/coder/projetos_fase1/pipex/pipex)
// ==2032== 
// ==2032== 
// ==2032== HEAP SUMMARY:
// ==2032==     in use at exit: 0 bytes in 0 blocks
// ==2032==   total heap usage: 4 allocs, 4 frees, 64 bytes allocated
// ==2032== 
// ==2032== All heap blocks were freed -- no leaks are possible
// ==2032== 
// ==2032== Use --track-origins=yes to see where uninitialised values come from
// ==2032== For lists of detected and suppressed errors, rerun with: -s
// ==2032== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
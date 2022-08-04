/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 19:40:04 by asoler            #+#    #+#             */
/*   Updated: 2022/08/04 16:57:57 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	trunc_spaces(char *space, char *cmd)
{
	int	r_letter;

	r_letter = 97;
	while (ft_strchr(cmd, r_letter))
		r_letter++;
	space[0] = r_letter;
	return (r_letter);
}

void	trim_each(char **path, int r_letter)
{
	int		i;
	char	*aux;

	i = 0;
	while (path[i])
	{
		if (ft_strlen(path[i]) > 2)
			path[i] = ft_strtrim(path[i], "'");
		if (r_letter)
		{
			aux = ft_strchr(path[i], r_letter);
			while (aux)
			{
				aux[0] = ' ';
				aux = ft_strchr(&aux[1], r_letter);
			}
		}
		i++;
	}
}

void	trunc_spaces_btwn_quotes(int *i, char *arg, char *aux, int *r_letter)
{
	while (arg[*i] != '\'' && arg[*i])
	{
		if (arg[*i] == ' ')
			*r_letter = trunc_spaces(&arg[*i], aux);
		*i += 1;
	}
}

void	verify_spaces(char *aux, int *r_letter)
{
	int		i;
	char	*arg;

	i = 1;
	arg = ft_strchr(aux, '\'');
	if (arg)
	{
		trunc_spaces_btwn_quotes(&i, arg, aux, r_letter);
		while (arg[i])
		{
			i++;
			while (arg[i] == ' ')
				i++;
			if (arg[i] == '\'')
				i++;
			trunc_spaces_btwn_quotes(&i, arg, aux, r_letter);
		}
	}
}

int	alloc_exec_paths(char *path, char ***cmd)
{
	char	*aux;
	int		r_letter;

	r_letter = 0;
	if (*path == 0)
	{
		*cmd = malloc(sizeof(char *) * 2);
		*cmd[0] = ft_strdup("");
		return (0);
	}
	aux = ft_strdup(path);
	verify_spaces(aux, &r_letter);
	*cmd = ft_split(aux, ' ');
	if (ft_strchr(aux, '\''))
		trim_each(*cmd, r_letter);
	// *cmd[0] = ft_strjoin("/usr/bin/", *cmd[0]);
	free(aux);
	return (0);
}

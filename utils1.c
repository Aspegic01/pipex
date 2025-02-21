/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:06:43 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/02/14 17:07:06 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static	void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static	char	*ft_get_env(const char *name, char **env)
{
	int	i;

	if (env == NULL || name == NULL)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) \
			== 0 && env[i][ft_strlen(name)] == '=')
			return (env[i] + ft_strlen(name) + 1);
		i++;
	}
	return (NULL);
}

static	char	*ft_get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return cmd;
		return NULL;
	}
	i = -1;
	allpath = ft_split(ft_get_env("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (ft_free_tab(s_cmd), exec);
		free(exec);
	}
	return (ft_free_tab(allpath), ft_free_tab(s_cmd), cmd);
}

void	execute_command(char *command, char **env)
{
	char	**argv;
	char	*command_path;

	argv = ft_split(command, ' ');
	if (!argv)
		ft_error("ft_split");
	command_path = ft_get_path(command, env);
	if (command_path == NULL)
	{
		free(command_path);
		ft_free_tab(argv);
		ft_error("bad command");
	}
	if (execve(command_path, argv, env) == -1)
	{
		free(command_path);
		ft_free_tab(argv);
		perror("execve");
		exit(1);
	}
	ft_free_tab(argv);
	if (command_path != command)
		free(command_path);
	exit(1);
}

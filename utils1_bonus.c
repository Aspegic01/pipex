/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:35:23 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/02/14 10:40:17 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

static	char	*remove_backslash(const char *str)
{
	int		len;
	int		j;
	int		i;
	char	*result;

	len = ft_strlen(str);
	result = (char *)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] != '\\')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

static	char	*ft_get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(ft_get_env("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (cmd);
}

void	execute_command(char *command, char **env)
{
	char	**argv;
	char	*command_path;
	char	*new;

	new = remove_backslash(command);
	argv = ft_split(new, ' ');
	if (!argv)
		ft_error("ft_split");
	command_path = ft_get_path(new, env);
	if (!command_path)
	{
		printf("Command not found: %s\n", new);
		ft_free_tab(argv);
		exit(1);
	}
	execve(command_path, argv, env);
	perror("execve");
	ft_free_tab(argv);
	if (command_path != new)
		free(command_path);
	exit(1);
}

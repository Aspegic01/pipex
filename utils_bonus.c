/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:15:48 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/02/12 10:15:52 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error(char *msg)
{
	perror(msg);
	exit(1);
}

static	void	ft_close(int p1, int p2)
{
	close(p1);
	close(p2);
}

static	void	handle_parent_process(int *i, int num_command, \
								int prev_pipefd[], int pipefd[])
{
	if (*i > 0)
		ft_close(prev_pipefd[0], prev_pipefd[1]);
	if (*i < num_command - 1)
	{
		prev_pipefd[0] = pipefd[0];
		prev_pipefd[1] = pipefd[1];
	}
	(*i)++;
}

static	void	handle_child_process(int i, int num_command, \
								int prev_pipefd[], int pipefd[])
{
	if (i > 0)
	{
		dup2(prev_pipefd[0], STDIN_FILENO);
		ft_close(prev_pipefd[0], prev_pipefd[1]);
	}
	if (i < num_command - 1)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		ft_close(pipefd[0], pipefd[1]);
	}
}

void	handle_pip_processes(char **av, int num_command, char **envp)
{
	int		pipefd[2];
	int		prev_pipefd[2];
	pid_t	pid;
	int		i;

	i = 0;
	while (i < num_command)
	{
		if (i < num_command - 1 && pipe(pipefd) == -1)
			ft_error("pipe");
		pid = fork();
		if (pid == -1)
			ft_error("fork");
		if (pid == 0)
		{
			handle_child_process(i, num_command, prev_pipefd, pipefd);
			execute_command(av[2 + i], envp);
		}
		else
			handle_parent_process(&i, num_command, prev_pipefd, pipefd);
	}
	if (num_command > 1)
		ft_close(prev_pipefd[0], prev_pipefd[1]);
	while(wait(NULL) > 0);
}

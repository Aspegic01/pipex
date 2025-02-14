/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:19:26 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/02/14 10:40:08 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_open_input_fd(char **av)
{
	int	input_fd;

	input_fd = open(av[1], O_RDONLY);
	if (input_fd == -1)
	{
		perror("open input_file");
		return (1);
	}
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 input_file");
		close(input_fd);
		return (1);
	}
	close(input_fd);
	return (0);
}

int	ft_open_output_fd(int ac, char **av)
{
	int	output_fd;

	output_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (output_fd == -1)
	{
		perror("open output_file");
		return (1);
	}
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 output_file");
		close(output_fd);
		return (1);
	}
	close(output_fd);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	int	i;

	if (ac < 5)
	{
		printf("Usage: %s <input_file> <cmd1> <cmd2> \
			... <output_file>\n", av[0]);
		exit(1);
	}
	i = 2;
	while (i < ac - 1)
	{
		if (av[i][0] == '.' || av[i][0] == '/')
		{
			printf("command not found");
			exit(1);
		}
		i++;
	}
	if (ft_open_input_fd(av))
		ft_error("the file doesnt open");
	if (ft_open_output_fd(ac, av))
		ft_error("the file ..");
	handle_pip_processes(av, ac - 3, envp);
}

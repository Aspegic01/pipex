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
	if (ac < 5)
	{
		perror("Usage: av <input_file> <cmd1> <cmd2> \
			... <output_file>\n");
		exit(1);
	}
	if (ft_open_input_fd(av))
		perror("no such input file");
	if (ft_open_output_fd(ac, av))
		ft_error("the file ..");
	handle_pip_processes(av, ac - 3, envp);
}

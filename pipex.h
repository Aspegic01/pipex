/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlabrirh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:08:08 by mlabrirh          #+#    #+#             */
/*   Updated: 2025/02/14 17:08:33 by mlabrirh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <threads.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include "./libft/libft.h"

void	execute_command(char *command, char **env);
void	handle_pip_processes(char **av, int num_command, char **envp);
void	ft_error(char *msg);

#endif

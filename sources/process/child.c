/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:21:55 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/15 17:32:29 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_only_child(t_data *data)
{
	char	**command;
	char	*path;

	command = ft_redirection(data, 0);
	ft_close_fds(data, NULL);
	if (!command[0])
		ft_quit(data, 0);
	if (ft_builtin(data, command) != 0)
		ft_quit(data, 0);
	path = ft_get_arg_path(data, command);
	execve(path, command, data->envp_tab);
	if (command[0][0] == '/')
		ft_builtin_slash(data, command[0]);
	ft_putstr3_fd(command[0], ": command", " not found\n");
	ft_quit(data, 1);
}

static void	ft_first_child(t_data *data, int **pipes, int i)
{
	char	**command;
	char	*path;

	if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
	{
		ft_close_fds(data, NULL);
		ft_perror(data,
			"First child: Error while duplicating file descriptor", 1);
		ft_quit(data, 1);
	}
	command = ft_redirection(data, i);
	ft_close_fds(data, NULL);
	if (!command[0])
		ft_quit(data, 0);
	if (ft_builtin(data, command) != 0)
		ft_quit(data, 0);
	path = ft_get_arg_path(data, command);
	execve(path, command, data->envp_tab);
	if (command[0][0] == '/')
		ft_builtin_slash(data, command[0]);
	ft_putstr3_fd(command[0], ": command", " not found\n");
	ft_quit(data, 1);
}

static void	ft_last_child(t_data *data, int **pipes, int i)
{
	char	**command;
	char	*path;

	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
	{
		ft_close_fds(data, NULL);
		ft_perror(data,
			"Last child: Error while duplicating file descriptor", 1);
		ft_quit(data, 1);
	}
	command = ft_redirection(data, i);
	ft_close_fds(data, NULL);
	if (!command[0])
		ft_quit(data, 0);
	if (ft_builtin(data, command) != 0)
		ft_quit(data, 0);
	path = ft_get_arg_path(data, command);
	execve(path, command, data->envp_tab);
	if (command[0][0] == '/')
		ft_builtin_slash(data, command[0]);
	ft_putstr3_fd(command[0], ": command", " not found\n");
	ft_quit(data, 1);
}

static void	ft_middle_child(t_data *data, int **pipes, int i)
{
	char	**command;
	char	*path;

	if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1
		|| dup2(pipes[i][1], STDOUT_FILENO) == -1)
	{
		ft_close_fds(data, NULL);
		ft_perror(data, "Error while duplicating file descriptor", 1);
		ft_quit(data, 1);
	}
	command = ft_redirection(data, i);
	ft_close_fds(data, NULL);
	if (!command[0])
		ft_quit(data, 0);
	if (ft_builtin(data, command) != 0)
		ft_quit(data, 0);
	path = ft_get_arg_path(data, command);
	execve(path, command, data->envp_tab);
	if (command[0][0] == '/')
		ft_builtin_slash(data, command[0]);
	ft_putstr3_fd(command[0], ": command", " not found\n");
	ft_quit(data, 1);
}

void	ft_child(t_data *data, int **pipes, int i)
{
	get_rediction(data, i);
	if (data->nb_cmd == 1)
		ft_only_child(data);
	else if (i == 0)
		ft_first_child(data, pipes, i);
	else if (i == data->nb_cmd - 1)
		ft_last_child(data, pipes, i);
	else
		ft_middle_child(data, pipes, i);
}

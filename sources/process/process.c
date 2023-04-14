/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/06 13:36:29 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_pipe_init(t_data *data)
{
	int	i;

	i = -1;
	data->pipes = ft_calloc((data->nb_cmd + 1), sizeof(int *));
	if (!data->pipes)
		perror("Memory allocation failed for data->pipes! ");
	while (++i < data->nb_cmd - 1)
	{
		data->pipes[i] = ft_calloc(2, sizeof(int));
		if (!data->pipes[i])
			ft_error(data, "Memory allocation failed for data->pipes[i]");
		if (pipe(data->pipes[i]) == -1)
			ft_error(data, "Pipe failed for data->pipes[i]");
	}

}

static void	ft_pipe_free(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_cmd - 1)
		free(data->pipes[i]);
	free(data->pipes);
	data->pipes = NULL;
}

static void	ft_process(t_data *data)
{
	int	i;
	int	pids;
	int	status;

	ft_pipe_init(data);
	i = -1;
	while (++i < data->nb_cmd)
	{
		pids = fork();
		if (pids == -1)
			ft_error(data, "Fork failed");
		if (pids == 0)
			ft_child(data, data->pipes, i);
	}
	ft_close_fds(data);
	while (--i >= 0)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
	}
printf("Last child exit code is %d\n", data->exit_code);
	ft_pipe_free(data);
}

void	ft_cmd(t_data *data)
{
	data->nb_cmd = ft_lstsize(data->cmd);
	if (data->nb_cmd == 1 && ft_builtin(data) != 0)
		return ;
	else
		ft_process(data);
}
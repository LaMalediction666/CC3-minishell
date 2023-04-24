/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:36:55 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/14 13:32:03 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern sig_atomic_t	g_exitcode;

static void	ft_pipe_init(t_data *data)
{
	int	i;

	i = -1;
	data->pipes = ft_calloc((data->nb_cmd + 1), sizeof(int *));
	if (!data->pipes)
		ft_perror(data, "Memory allocation failed: data->pipes", 12);
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
	ft_close_fds(data, NULL);
	g_exitcode += 2;
	while (--i >= 0)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_code = WTERMSIG(status) + 128;
	}
	g_exitcode -= 2;
	ft_pipe_free(data);
}

void	ft_cmd(t_data *data)
{
	char	**command;

	command = s_read_cnt(data->cmd)->command;
	data->nb_cmd = ft_lstsize(data->cmd);
	if (data->nb_cmd == 1 && ft_inredic_count(command) == 0
		&& ft_outredic_count(command) == 0 && ft_builtin(data, command) != 0)
		return ;
	ft_process(data);
}

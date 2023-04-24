/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:00:26 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/24 14:11:41 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern sig_atomic_t	g_exitcode;


static void	ft_error_heredoc(t_data *data, int *here_doc_fd)
{
	close(here_doc_fd[0]);
	close(here_doc_fd[1]);
	ft_error(data, "Error while using here_doc");
}

static void	ft_stop_heredoc(t_data *data, int *here_doc_fd, char *input)
{
	g_exitcode -= 1;
	close(here_doc_fd[0]);
	close(here_doc_fd[1]);
	if (input)
		free(input);
	ft_quit(data, 2);
}

static void	ft_here_doc(t_data *data, int *here_doc_fd, char *limiter)
{
	char	*input;
	int		limiter_len;
	int		intput_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		ft_putstr_fd("here_doc> ", STDIN_FILENO);
		input = get_next_line(STDIN_FILENO);
		if (!input)
			ft_error_heredoc(data, here_doc_fd);
		if (g_exitcode == 1 || g_exitcode == 3)
			ft_stop_heredoc(data, here_doc_fd, input);
		intput_len = ft_strlen(input);
		if (ft_strncmp(input, limiter, limiter_len) == 0
			&& intput_len == limiter_len + 1 && input[limiter_len] == '\n')
			break ;
		if (write(here_doc_fd[1], input, intput_len) == -1)
			ft_perror(data, "Error while writing in the here_doc's pipe!", 1);
		free(input);
	}
	free(input);
}

void	ft_input_heredoc(t_data *data, char *limiter, int last_redir)
{
	if (pipe(data->here_doc_fd) == -1)
	{	
		ft_error(data, "Pipe failed for here_doc!");
	}
	ft_here_doc(data, data->here_doc_fd, limiter);
	if (last_redir == 1)
	{
		ft_close_fds(data, data->here_doc_fd);
		return ;
	}
	if (dup2(data->here_doc_fd[0], STDIN_FILENO) == -1)
	{
		ft_close_fds(data, data->here_doc_fd);
		ft_error(data, "Error while duplicating file descriptor! ");
	}
	close(data->here_doc_fd[0]);
	close(data->here_doc_fd[1]);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:06:52 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/14 11:20:33 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// input[0] : 0 = < ; 1 = <<
// input[1] : file or limiter

static void	ft_input_file(t_data *data, char *file, int last_redir)
{
	int	infile;

	infile = open(file, O_RDONLY, 0644);
	if (infile == -1)
		ft_perror(data, "Error when opening file1", 1);
	if (last_redir == 1)
	{
		close(infile);
		return ;
	}
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		ft_close_fds(data, NULL);
		close(infile);
		ft_perror(data, "Error while duplicating file descriptor", 1);
		ft_quit(data, 1);
	}
}

static void	ft_close_hd_fd(int *here_doc_fd)
{
	close(here_doc_fd[0]);
	close(here_doc_fd[1]);
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
		{
			ft_close_hd_fd(here_doc_fd);
			free(here_doc_fd);
			ft_error(data, "Error while using here_doc");
		}
		intput_len = ft_strlen(input);
		if (ft_strncmp(input, limiter, limiter_len) == 0
			&& intput_len == limiter_len)
			break ;
		if (write(here_doc_fd[1], input, intput_len) == -1
			|| write(here_doc_fd[1], "\n", 1) == -1)
			ft_perror(data, "Error while writing in the here_doc's pipe!", 1);
		free(input);
	}
	free(input);
}

static void	ft_input_heredoc(t_data *data, char *limiter, int last_redir)
{
	data->here_doc_fd = ft_calloc(3, sizeof(int *));
	if (!data->here_doc_fd)
		ft_error(data, "Memory allocating failed for here_doc_fd");
	if (pipe(data->here_doc_fd) == -1)
	{	
		free(data->here_doc_fd);
		ft_error(data, "Pipe failed for here_doc!");
	}
	ft_here_doc(data, data->here_doc_fd, limiter);
	if (last_redir == 1)
	{
		ft_close_fds(data, data->here_doc_fd);
		free(data->here_doc_fd);
		return ;
	}
	if (dup2(data->here_doc_fd[0], STDIN_FILENO) == -1)
	{
		ft_close_fds(data, data->here_doc_fd);
		free(data->here_doc_fd);
		ft_error(data, "Error while duplicating file descriptor! ");
	}
	ft_close_hd_fd(data->here_doc_fd);
}

void	ft_input_redirection(t_data *data, char **input)
{
	char	*tmp;
	int		last_redir;
	int		i;

	i = 0;
	while (input[i] && input[i + 1])
	{
		if (!input[i + 2])
			last_redir = 0;
		else
			last_redir = 1;
		if (input[i][0] == '0')
			ft_input_file(data, input[i + 1], last_redir);
		else if (input[i][0] == '1')
		{
			tmp = input[i + 1];
			input[i + 1] = ft_strjoin(input[i + 1], "\n");
			free(tmp);
			ft_input_heredoc(data, input[i + 1], last_redir);
		}
		i += 2;
	}
}

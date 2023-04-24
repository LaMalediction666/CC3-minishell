/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:06:52 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/24 14:12:53 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern sig_atomic_t	g_exitcode;

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

void	ft_input_redirection(t_data *data, char **input)
{
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
			ft_input_heredoc(data, input[i + 1], last_redir);
		i += 2;
	}
}

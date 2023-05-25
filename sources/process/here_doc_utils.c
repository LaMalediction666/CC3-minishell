/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:00:26 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/25 13:53:55 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern sig_atomic_t	g_exitcode;

void	ft_check_hd_expand(t_pipeline *pipe, char *limiter)
{
	if (limiter[0] < 0)
	{
		pipe->here_doc_expand = 1;
		limiter[0] *= -1;
	}
	else
		pipe->here_doc_expand = 0;
}

void	ft_error_heredoc(t_data *data, int *here_doc_fd, char *limiter)
{
	ft_putstr_fd("minishell: warning: here-document limiter wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("'\n", 2);
	ft_close(here_doc_fd[0]);
	ft_close(here_doc_fd[1]);
	ft_quit(data, 1);
}
//message when ctrl+d in stead of ctrl+c

void	ft_stop_heredoc(t_data *data, int *here_doc_fd, char *input)
{
	g_exitcode--;
	ft_close(here_doc_fd[0]);
	ft_close(here_doc_fd[1]);
	if (input)
		free(input);
	ft_quit(data, 2);
}

char	*ft_here_doc_expand(t_data *data, t_pipeline *pipe, char *input)
{
	int	i;

	i = 0;
	if (pipe->here_doc_expand == 1)
		return (input);
	while (input[i])
	{
		if (input[i] == '$')
			input = expand_handler(data, input, &i);
		i++;
	}
	return (input);
}

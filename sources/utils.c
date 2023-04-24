/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:37:42 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/24 13:53:45 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_c_in(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_data_init(t_data *data)
{
	data->nb_cmd = 0;
	data->pipes = NULL;
	data->cmd = NULL;
	data->exit_code = 0;
	ft_envp(data);
	data->envp_tab = ft_lst_to_tabtab(data, data->envp);
}

void	ft_close_fds(t_data *data, int *here_doc_fd)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd - 1)
	{
		close(data->pipes[i][0]);
		close(data->pipes[i][1]);
		i++;
	}
	if (here_doc_fd)
	{
		close(here_doc_fd[0]);
		close(here_doc_fd[1]);
	}
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*res;
	char	*tmp;

	if (!s1 && !s2)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (perror("Error while allocating memory for char **envp!"), NULL);
	if (!s3)
		return (tmp);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	if (!res)
		return (perror("Error while allocating memory for char **envp!"), NULL);
	return (res);
}

void	ft_print_tabtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%d]\t=\t%s\n", i, tab[i]);
		i++;
	}
}

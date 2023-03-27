/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:03:17 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/27 14:44:20 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_rfree_tab(char **tab, int i)
{
	while (i > 0)
	{
		i--;
		free(tab[i]);
	}
	free(tab);
}

void	ft_quit(t_data *data)
{
	int	i;

	i = -1;
	if (data->pipes != NULL)
	{
		while (++i < data->nb_cmd - 1)
			free(data->pipes[i]);
		free(data->pipes);
	}
	free_lst(&data->cmd);
	ft_free_envplst(data);
	ft_free_envptab(data);
}

void	ft_error(t_data *data, char *s)
{
	ft_putstr_fd("\nError\n", 2);
	if (s)
		ft_putstr_fd(s, 2);
	perror(" ");
	ft_putstr_fd("\n", 2);
	ft_quit(data);
	exit (1);
}

void	ft_free_envptab(t_data *data)
{
	int	i;

	i = 0;
	if (!data->envp_tab)
		return ;
	while (data->envp_tab[i])
	{
		free(data->envp_tab[i]);
		i++;
	}
	free(data->envp_tab);
	data->envp_tab = NULL;
}

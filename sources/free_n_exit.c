/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_n_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvogel <mvogel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:02:45 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/03/08 16:51:32 by mvogel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static void	free_del(void **content)
{
	free_tab((char**)content);
	content = NULL;
}

void	free_lst(t_list **cmd)
{
	ft_lstclear(cmd, free_del);
	return ;
}

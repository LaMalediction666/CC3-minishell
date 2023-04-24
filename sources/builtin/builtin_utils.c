/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:21:55 by julien            #+#    #+#             */
/*   Updated: 2023/04/12 17:52:29 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr3_fd(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
}

void	ft_update_envptab(t_data *data)
{
	ft_free_envptab(data);
	data->envp_tab = ft_lst_to_tabtab(data, data->envp);
}

int	ft_check_exportvar(char *variable)
{
	int	i;

	i = 1;
	if (variable[0] == '='
		|| (ft_isalpha(variable[0]) == 0 && variable[0] != '_'))
		return (1);
	while (variable[i] && variable[i] != '=')
	{
		if (ft_isalnum(variable[i]) == 0 && variable[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

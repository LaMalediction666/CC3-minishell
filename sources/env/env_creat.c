/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:25:51 by jmoutous          #+#    #+#             */
/*   Updated: 2023/05/24 10:34:18 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_creat_variable(t_data *data, char *variable, char *value)
{
	t_envp		*tmp;

	tmp = ft_calloc(1, sizeof(t_envp));
	if (!tmp)
		ft_error(data, "Memory allocation failed: envp_init", 12);
	tmp->variable = strdup(variable);
	if (!tmp->variable)
		ft_error(data, "Memory allocation failed: envp_creat", 12);
	if (value)
	{
		tmp->value = strdup(value);
		if (!tmp->value)
			ft_error(data, "Memory allocation failed: envp_creat", 12);
	}
	else
		tmp->value = NULL;
	tmp->next = NULL;
	ft_envadd_back(&data->envp, tmp);
}

void	ft_creat_envp(t_data *data)
{
	data->envp = NULL;
	ft_creat_variable(data, "PWD", getcwd(NULL, 0));
	ft_creat_variable(data, "OLDPWD", NULL);
	ft_creat_variable(data, "SHLVL", "1");
}

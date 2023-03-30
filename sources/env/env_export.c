/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julien <julien@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:42:18 by jmoutous          #+#    #+#             */
/*   Updated: 2023/03/29 16:27:05 by julien           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_export_add(t_data *data, int i)
{
	t_envp	*tmp;
	char	**buffer;

	tmp = ft_calloc(1, sizeof(t_envp));
	if (!tmp)
		perror("Error while allocating memory for envp!");
	if (ft_is_c_in(data->cmd->content[i], '=') == 1)
	{
		buffer = ft_split_var(data->cmd->content[i]);
		if (!buffer)
			ft_error(data, "Memory allocation failed for export_add!");
		tmp->variable = buffer[0];
		tmp->value = buffer[1];
		free(buffer);
	}
	else
	{
		tmp->variable = ft_strdup(data->cmd->content[i]);
		tmp->value = NULL;
	}
	tmp->next = NULL;
	ft_envadd_back(&data->envp, tmp);
}

static int	ft_varlen(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

static t_envp	*ft_is_var_in_env(t_data *data, int i)
{
	t_envp				*tmp;
	long unsigned int	n;

	tmp = data->envp;
	n = ft_varlen(data->cmd->content[i]);
	while (tmp)
	{
		if (ft_strncmp(data->cmd->content[i], tmp->variable, n) == 0
			&& ft_strlen(tmp->variable) == n)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	ft_export_mod(t_data *data, t_envp *var, int i)
{
	char	**buffer;

	if (ft_is_c_in(data->cmd->content[i], '=') == 1)
	{
		buffer = ft_split_var(data->cmd->content[i]);
		if (!buffer)
			ft_error(data, "Memory allocation failed for export_mod!");
		free(var->value);
		var->value = buffer[1];
		free(buffer[0]);
		free(buffer);
	}
}

void	ft_export(t_data *data)
{
	t_envp	*var;
	int		i;

	i = 1;
	while (data->cmd->content[i])
	{
		var = ft_is_var_in_env(data, i);
		if (var != NULL)
			ft_export_mod(data, var, i);
		else
			ft_export_add(data, i);
		i++;
	}
	ft_free_envptab(data);
	data->envp_tab = ft_lst_to_tabtab(data->envp);
}
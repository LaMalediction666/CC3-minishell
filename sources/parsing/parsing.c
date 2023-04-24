/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdidesmartin <mehdidesmartin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:15:10 by mehdidesmar       #+#    #+#             */
/*   Updated: 2023/04/14 16:16:46 by mehdidesmar      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_chain(t_data *data)
{
	t_list *cp;
	int i = 0;

	cp = data->cmd;
	ft_printf("the parsed input is : ");
	while (cp)
	{
		i = 0;
		while (s_read_cnt(cp)->command[i])
		{
			printf("%s ", s_read_cnt(cp)->command[i]);
			i++;
		}
		if (i > 1)
			printf("| ");
		cp = cp->next; 
	}
	printf("\n");
	return ;
}

void	print_tab(char **pipe_tab)
{
	int i = 0;

	while (pipe_tab[i])
	{
		printf("tab[%d] : %s\n", i, pipe_tab[i]);
		i++;
	}
	return ;
}

////////////////////////////////////////////////////////////////////////////////

void	create_chain(t_list **cmd, void *content)
{
	if (*cmd == NULL)
		*cmd = ft_lstnew(content);
	else
		ft_lstadd_back(cmd, ft_lstnew(content));
	return ;
}

void	split_tab(t_list **cmd, char **pipe_tab)
{
	int		i;
	char	**pipe;
	void	*adress;

	i = 0;
	pipe = NULL;
	while (pipe_tab[i])
	{
		pipe = split_token(pipe_tab[i], " \t");//ft_split(pipe_tab[i], ' ');
		if (!pipe)
			return (perror("Error\n"), free(pipe_tab));
		adress = s_init(pipe, NULL, NULL);
		create_chain(cmd, adress);//replace input and output there
		i++;
	}
	// free_tab(pipe_tab);
}

int	parsing(t_data *data, char *input)
{
	char	**pipe_tab;
	int		nb_p;

	nb_p = nb_pipes(input);
	if (nb_p == -1)
		return (-1);//quote pas fermée
	pipe_tab = NULL;
	pipe_tab = create_tab(pipe_tab, input, nb_p);
	// print_tab(pipe_tab);
	dollar(data, pipe_tab);
	print_tab(pipe_tab);
	split_tab(&data->cmd, pipe_tab);
	// print_chain(data);
	return (0);
}





// int	parsing(t_data *data, char *input)
// {
// 	int		nb_p;

// 	nb_p = nb_pipes(input);
// 	if (nb_p == -1)
// 		return (-1);
// 	// ft_printf("nb_pipes : %d\n", nb_p);
// 	split_pipes(data, nb_p, input);
// 	print_chain(data);
// 	// dollar(data);
// 	return (0);
// }


// valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes ./minishell

















// void	create_chain(t_list **cmd, char **pipe)
// {
// 	if (*cmd == NULL)
// 		*cmd = ft_lstnew((void**)pipe);
// 	else
// 		ft_lstadd_back(cmd, ft_lstnew((void **)pipe));
// 	return ;
// }

// dabbord checker les quotes, puis deplacer le i a la fin des quotes,
// ensuite split au pipe le bloc
// chaque maillon contient un pipe, chqaue str du tab est un token un pipe
// dabbord creer un tab (pipe_tab) avec a chaque str un pipe, le traiter puis
// ensuite a la fin split et put in chain



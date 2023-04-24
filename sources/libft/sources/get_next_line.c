/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoutous <jmoutous@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:38:42 by jmoutous          #+#    #+#             */
/*   Updated: 2023/04/24 13:32:57 by jmoutous         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*end_line_from_stock(char *stock)
{
	char	*end_line;
	int		i;

	i = 0;
	if (!stock || stock[0] == 0)
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
		i++;
	end_line = ft_calloc(i + 1, sizeof(char));
	if (!end_line)
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
	{
		end_line[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n')
		end_line[i] = stock[i];
	return (end_line);
}

static void	ft_new_stock(char *stock)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (stock[i] != 0 && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
		i++;
	while (stock[i + j])
	{
		stock[j] = stock [i + j];
		j++;
	}
	stock[j] = 0;
}

static int	is_n_in(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	stock[BUFFER_SIZE + 1];
	char		*line;
	char		*end_line;
	int			check_read;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	check_read = 1;
	line = NULL;
	while (check_read > 0)
	{
		if (is_n_in(stock) == 1)
		{
			end_line = end_line_from_stock(stock);
			line = ft_strjoin_g(line, end_line);
			return (free(end_line), ft_new_stock(stock), line);
		}
		if (stock[0] != 0)
			line = ft_strjoin_g(line, stock);
		check_read = read(fd, stock, BUFFER_SIZE);
		stock[check_read] = 0;
	}
	if (check_read == -1)
		return (stock[0] = 0, free(line), NULL);
	return (line);
}

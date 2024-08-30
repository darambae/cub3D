/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:07:55 by dabae             #+#    #+#             */
/*   Updated: 2024/03/14 15:17:48 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

t_line	*ft_lastnode(t_line *buf_list)
{
	t_line	*current;

	current = buf_list;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	prep_line(char **line, t_line *buf_list)
{
	int	i;
	int	j;

	j = 0;
	while (buf_list)
	{
		i = 0;
		while (buf_list->str_tmp[i] && buf_list->str_tmp[i] != '\n')
		{
			i++;
			j++;
		}
		if (buf_list->str_tmp[i] == '\n')
			j++;
		buf_list = buf_list->next;
	}
	*line = malloc(sizeof(char) * (j + 1));
}

void	free_list(t_line *buf_list)
{
	t_line	*tmp;

	while (buf_list)
	{
		tmp = buf_list;
		buf_list = buf_list->next;
		free(tmp->str_tmp);
		free(tmp);
	}
}

int	found_n(t_line *buf_list)
{
	int		i;
	t_line	*last;

	if (!buf_list)
		return (0);
	last = ft_lastnode(buf_list);
	i = 0;
	while (last->str_tmp[i])
	{
		if (last->str_tmp[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

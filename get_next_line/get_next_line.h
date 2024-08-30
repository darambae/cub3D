/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabae <dabae@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:23:50 by dabae             #+#    #+#             */
/*   Updated: 2024/03/14 15:10:09 by dabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_line
{
	char			*str_tmp;
	struct s_line	*next;
}			t_line;

char	*get_next_line(int fd);

int		found_n(t_line *buf_list);

int		get_strlen(char *s);

void	free_list(t_line *buf_list);

void	prep_line(char **line, t_line *buf_list);

t_line	*ft_lastnode(t_line *buf_list);
#endif

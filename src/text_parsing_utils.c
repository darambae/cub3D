#include "cub.h"

int	skip_space(char *line)
{
	if (!ft_strchr(" \t\n\v\r", *line))//no space after id
		return (-1);
	while (ft_strchr(" \t\n\v\r", *line))//skip space
		line++;
	if (!*line)//no color after spaces
		return (-1);
	return (0);
}

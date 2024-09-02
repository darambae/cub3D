#include "../cub.h"

void    map_parsing(t_param *param, char *line)
{
    int i;
    int j;
    int k;
    //int len;

    i = 0;
    j = 0;
    k = 0;
    //len = ft_strlen(line);
    while (line[i] != '\0')
    {
        if (line[i] == '1')
        {
            param->map[j][k].x = k;
            param->map[j][k].y = j;
            param->map[j][k].z = 1;
            k++;
        }
        else if (line[i] == '0')
        {
            param->map[j][k].x = k;
            param->map[j][k].y = j;
            param->map[j][k].z = 0;
            k++;
        }
        i++;
    }
    param->map_width = k;
    param->map_lenth = j;
}
#include "../cub.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	my_mlxx_pixel_put(t_param *param, int x, int y, int color)
{
	char	*dst;

	dst = param->addr + (y * SCREEN_W + x) * (param->bits_per_pixel / 8);
	*(unsigned int *)dst = color;
}

unsigned int get_pixel(t_param *param, int x, int y)
{
    // Ensure the pixel coordinates are within bounds
    if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
        return 0; // Return black or any default color for out-of-bounds

    // Calculate the pixel index in the image buffer
    char *pixel_addr = param->addr + (y * param->map_w + x * (param->bits_per_pixel / 8));

    // Dereference the pixel data, assuming 32-bit color (4 bytes per pixel)
    unsigned int color = *(unsigned int *)pixel_addr;

    return color;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:16:38 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/29 17:53:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	image_pixel_set(unsigned int *pixels_start_prt, int pixels_per_line,
						t_yx_value *pixel_position, unsigned int pixel_color)
{
	unsigned int		*pixel_ptr;

	pixel_ptr = pixels_start_prt + (pixels_per_line * pixel_position->y)
		+ pixel_position->x;
	*pixel_ptr = pixel_color;
	return ;
}

static void	print_something(t_image_data *image_data,
													t_yx_value *pixel_position)
{
	int					y_end_point;
	unsigned int		color;

	color = 0x00FF0000;
	y_end_point = pixel_position->y + 55;
	while (pixel_position->y < y_end_point)
	{
		image_pixel_set(image_data->pixels_start_prt,
			image_data->pixels_per_line, pixel_position, color);
		pixel_position->y++;
	}
	return ;
}

static t_image_data	*get_image_data(void *image)
{
	t_image_data	*image_data;

	image_data = (t_image_data *)ft_memalloc(sizeof(*image_data));
	image_data->pixels_start_prt = (unsigned int *)mlx_get_data_addr(image,
			&image_data->bits_per_pixel,
			&image_data->size_line, &image_data->endian);
	image_data->pixels_per_line
		= (int)(image_data->size_line / (image_data->bits_per_pixel / 8));
	return (image_data);
}

int	main(void)
{
	t_window		*window;
	t_yx_value		image_size;
	t_yx_value		pixel_position;

	window = window_initialize("Fractol!");
	image_size.y = 600;
	image_size.x = 900;
	window->image = mlx_new_image(window->mlx, image_size.x,
			image_size.y);
	window->image_status = 0;
	window->image_data = get_image_data(window->image);
	pixel_position.y = 200;
	pixel_position.x = 400;
	print_something(window->image_data, &pixel_position);
	mlx_put_image_to_window(window->mlx, window->win, window->image,
		0, 0);
	mlx_loop(window->mlx);
	window_release(&window);
	return (0);
}

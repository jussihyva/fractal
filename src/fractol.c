/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:16:38 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/29 18:06:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	fractal_julia_create(window->image_data);
	mlx_put_image_to_window(window->mlx, window->win, window->image,
		0, 0);
	mlx_loop(window->mlx);
	window_release(&window);
	return (0);
}

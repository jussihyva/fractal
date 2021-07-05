/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:16:38 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/05 14:30:47 by jkauppi          ###   ########.fr       */
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
	mlx_loop(window->mlx);
	window_release(&window);
	return (0);
}

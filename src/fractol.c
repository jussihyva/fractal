/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:16:38 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/29 14:44:39 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(void)
{
	t_window		*window;
	t_yx_value		image_size;

	window = window_initialize("Fractol!");
	image_size.y = 600;
	image_size.x = 900;
	window->image = (t_img *)mlx_new_image(window->mlx, image_size.x,
			image_size.y);
	window->image_status = 0;
	mlx_loop(window->mlx);
	window_release(&window);
	return (0);
}

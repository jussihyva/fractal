/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:16:38 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/06 00:07:11 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(void)
{
	t_window		*window;

	window = window_initialize("Fractol!");
	window->image = mlx_new_image(window->mlx, window->window_size.x,
			window->window_size.y);
	window->image_status = 0;
	window->image_data = get_image_data(window->image);
	mlx_loop(window->mlx);
	window_release(&window);
	return (0);
}

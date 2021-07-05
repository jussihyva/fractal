/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:49:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/05 15:25:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fractol.h"

int	mouse_button_press(int keycode, int x, int y, t_window *window)
{
	t_fractal_data		*fractal_data;

	if (keycode == 4 || keycode == 5)
	{
		fractal_data = window->fractal_data;
		if (keycode == 4)
			fractal_data->zoom += 0.3;
		else if (fractal_data->zoom > 1)
			fractal_data->zoom -= 0.3;
		else
			fractal_data->zoom = 1;
		ft_printf("ZOOM = %0.1f\n", fractal_data->zoom);
		fractal_julia_create(window->image_data, window->fractal_data);
		window->window_action = 1;
	}
	else
		ft_printf("Key: %d, Mouse location: x:%d, y:%d\n", keycode, x, y);
	return (0);
}

int	mouse_motion_notify(int x, int y, t_window *window)
{
	t_yx_value_double	shape_factor;
	t_fractal_data		*fractal_data;

	ft_printf("Y:%d X:%d\n", y, x);
	if (x >= 0 && x < window->window_size.x
		&& y >= 0 && y < window->window_size.y)
	{
		fractal_data = window->fractal_data;
		shape_factor.y = (double)(window->window_size.y / 2 - y)
			/ (window->window_size.y / 2) * 0.01;
		shape_factor.x = (double)(window->window_size.x / 2 - x)
			/ (window->window_size.x / 2) * 0.01;
		fractal_data->shape_real = -0.7 + shape_factor.x;
		fractal_data->shape_imaginary = 0.27015 + shape_factor.y;
		fractal_julia_create(window->image_data, window->fractal_data);
		window->window_action = 1;
	}
	return (0);
}

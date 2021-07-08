/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:49:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/08 10:37:17 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		window->window_action = E_UPDATE_IMAGE;
	}
	else
		ft_printf("Key: %d, Mouse location: x:%d, y:%d\n", keycode, x, y);
	return (0);
}

void	update_shape_values(t_fractal_data *fractal_data,
										t_yx_value *window_size, int x, int y)
{
	if (fractal_data->type_of_fractal == E_JULIA)
		update_shape_values_julia(&fractal_data->shape,
			window_size, y, x);
	else if (fractal_data->type_of_fractal == E_POLYNOMIAL)
		update_shape_values_polynomial(&fractal_data->shape,
			window_size, y, x);
	else if (fractal_data->type_of_fractal == E_MANDELBROT)
		update_offset_values_mandelbrot(&fractal_data->offset,
			window_size, y, x);
	return ;
}

int	mouse_motion_notify(int x, int y, t_window *window)
{
	static t_yx_value	prev_pos = {.x = 0, .y = 0};
	t_fractal_data		*fractal_data;

	if (x >= 0 && x < window->window_size.x && y >= 0
		&& y < window->window_size.y)
	{
		fractal_data = window->fractal_data;
		if (ft_abs(x - prev_pos.x) > 5 || ft_abs(y - prev_pos.y) > 5)
		{
			update_shape_values(fractal_data, &window->window_size, x, y);
			window->window_action = E_UPDATE_IMAGE;
			prev_pos.y = y;
			prev_pos.x = x;
			ft_printf("Y:%d X:%d\n", y, x);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:58:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/06 00:12:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	window_close(t_window *window)
{
	(void)window;
	exit(0);
	return (0);
}

int	window_render_frame(t_window *window)
{
	if (window->window_action)
	{
		ft_printf("%s\n", "MOI!");
		mlx_put_image_to_window(window->mlx, window->win, window->image,
			0, 0);
		window->window_action = 0;
	}
	return (0);
}

static void	window_activate_hook_events(t_window *window)
{
	mlx_hook(window->win, 2, 0x01, keyboard_key_press, (void *)window);
	mlx_hook(window->win, 4, 0x04, mouse_button_press, (void *)window);
	mlx_hook(window->win, 6, 0x40, mouse_motion_notify, (void *)window);
	mlx_hook(window->win, 17, 0x00, window_close, (void *)window);
	mlx_loop_hook(window->mlx, window_render_frame, (void *)window);
	return ;
}

t_window	*window_initialize(char *window_name)
{
	t_window	*window;

	window = (t_window *)ft_memalloc(sizeof(*window));
	window->window_size.y = 600;
	window->window_size.x = 900;
	window->fractal_data
		= (t_fractal_data *)ft_memalloc(sizeof(*window->fractal_data));
	window->fractal_data->shape_real = -0.7;
	window->fractal_data->shape_imaginary = 0.27015;
	window->fractal_data->zoom = 1;
	ft_memcpy(&window->fractal_data->fractal_size, &window->window_size,
		sizeof(window->fractal_data->fractal_size));
	window->mlx = (void *)mlx_init();
	window->win = mlx_new_window(window->mlx, window->window_size.x,
			window->window_size.y, window_name);
	window_activate_hook_events(window);
	return (window);
}

void	window_release(t_window **window)
{
	mlx_destroy_image((*window)->mlx, (*window)->image);
	mlx_destroy_window((*window)->mlx, (*window)->win);
	ft_memdel((void **)&(*window)->fractal_data);
	return ;
}

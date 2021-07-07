/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:58:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/07 14:44:01 by jkauppi          ###   ########.fr       */
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
	if (window->window_action == E_UPDATE_IMAGE)
	{
		window->window_action = E_UPDATE_ONGOING;
		ft_printf("%s\n", "MOI!");
		if (window->fractal_data->type_of_fractal == E_JULIA)
			fractal_julia_create(window->image_data, window->fractal_data);
		else
			fractal_mandelbrot_create(window->image_data, window->fractal_data);
		mlx_put_image_to_window(window->mlx, window->win, window->image,
			0, 0);
		if (window->window_action == E_UPDATE_ONGOING)
			window->window_action = E_NO_ACTION;
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

t_window	*window_initialize(char *fractal)
{
	t_window	*window;
	char		*window_name;

	if (ft_strequ(fractal, "j"))
		window_name = ft_strdup("Fractal: Julia");
	else if (ft_strequ(fractal, "m"))
		window_name = ft_strdup("Fractal: Julia");
	else
		window_name = ft_strdup("Fractal!");
	window = (t_window *)ft_memalloc(sizeof(*window));
	window->window_size.y = 600;
	window->window_size.x = 900;
	window->fractal_data = fractal_initialize(fractal, &window->window_size);
	window->mlx = (void *)mlx_init();
	window->win = mlx_new_window(window->mlx, window->window_size.x,
			window->window_size.y, window_name);
	window_activate_hook_events(window);
	ft_strdel(&window_name);
	return (window);
}

void	window_release(t_window **window)
{
	mlx_destroy_image((*window)->mlx, (*window)->image);
	mlx_destroy_window((*window)->mlx, (*window)->win);
	ft_memdel((void **)&(*window)->fractal_data);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:58:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/29 10:41:42 by jkauppi          ###   ########.fr       */
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
	window->window_size.x = 900;
	window->window_size.y = 600;
	window->mlx = mlx_init();
	window->win = mlx_new_window(window->mlx, window->window_size.x,
			window->window_size.y, window_name);
	window_activate_hook_events(window);
	return (window);
}

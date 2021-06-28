/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:58:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/29 00:20:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	window_close(t_window *window)
{
	(void)window;
	exit(0);
	return (0);
}

void	window_initialize(t_window *window, char *window_name)
{
	window->win = mlx_new_window(window->mlx, window->window_size.x,
			window->window_size.y, window_name);
	mlx_hook(window->win, 2, 0x01, keyboard_key_press, window);
	mlx_hook(window->win, 4, 0x04, mouse_button_press, window);
	mlx_hook(window->win, 6, 0x40, mouse_motion_notify, window);
	mlx_hook(window->win, 17, 0x00, window_close, window);
	mlx_hook(window->win, 33, 0x00, window_close, window);
	return ;
}

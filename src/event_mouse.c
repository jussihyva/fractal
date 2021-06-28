/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:49:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/28 18:54:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fractol.h"

int	mouse_button_press(int keycode, int x, int y, t_window *window)
{
	(void)window;
	ft_printf("Key: %d, Mouse location: x:%d, y:%d\n", keycode, x, y);
	return (0);
}

int	mouse_motion_notify(int x, int y, t_window *window)
{
	(void)window;
	(void)x;
	(void)y;
	ft_printf("Y:%d X:%d\n", y, x);
	return (0);
}

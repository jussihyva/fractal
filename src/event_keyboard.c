/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_keyboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 18:55:25 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/06 09:53:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	keyboard_key_press(int keycode, t_window *window)
{
	if (keycode == 65307 || keycode == ESC)
	{
		ft_printf("Request (ESC key pressed) to exit.\n");
		window_close(window);
	}
	else
		ft_printf("keycode: %#x\n", keycode);
	return (0);
}

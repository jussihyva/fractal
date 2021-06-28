/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:16:38 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/28 19:04:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	render_frame(t_window *window)
{
	if (window->window_action)
	{
		ft_printf("%s\n", "MOI!");
		window->window_action = 0;
	}
	return (0);
}

int	main(void)
{
	t_window	window;

	window.window_size.x = 900;
	window.window_size.y = 600;
	window.mlx = mlx_init();
	window_initialize(&window, "Fractol!");
	mlx_loop_hook(window.mlx, render_frame, (void *)&window);
	mlx_loop(window.mlx);
	return (0);
}

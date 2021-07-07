/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 23:49:19 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/07 17:25:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fractal_data	*fractal_initialize(char *fractal, t_yx_value *window_size)
{
	t_fractal_data		*fractal_data;

	fractal_data = (t_fractal_data *)ft_memalloc(sizeof(*fractal_data));
	fractal_data->shape.real = -0.7;
	fractal_data->shape.imaginary = 0.27015;
	fractal_data->zoom = 1;
	if (ft_strequ(fractal, "j"))
		fractal_data->type_of_fractal = E_JULIA;
	else if (ft_strequ(fractal, "p"))
		fractal_data->type_of_fractal = E_POLYNOMIAL;
	else
		fractal_data->type_of_fractal = E_MANDELBROT;
	ft_memcpy(&fractal_data->fractal_size, window_size,
		sizeof(fractal_data->fractal_size));
	return (fractal_data);
}

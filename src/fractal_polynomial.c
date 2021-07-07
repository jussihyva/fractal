/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_polynomial.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:18:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/07 18:27:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_new_values(t_fractal_data *fractal_data,
							t_yx_value *pixel_position)
{
	t_yx_value		*image_size;

	image_size = &fractal_data->fractal_size;
	fractal_data->new.real = 2 * (pixel_position->x - image_size->x / 2)
		/ (0.5 * fractal_data->zoom * image_size->x) + fractal_data->offset.x;
	fractal_data->new.imaginary = 2 * (pixel_position->y - image_size->y / 2)
		/ (0.5 * fractal_data->zoom * image_size->y) + fractal_data->offset.y;
	return ;
}

void	update_shape_values_polynomial(t_fractal_shape *shape,
										t_yx_value *window_size, int y, int x)
{
	t_yx_value_double	shape_factor;

	shape_factor.y = (double)(window_size->y / 2 - y) / (window_size->y / 2)
		* 0.1;
	shape_factor.x = (double)(window_size->x / 2 - x) / (window_size->x / 2)
		* 0.1;
	shape->real = -1 + shape_factor.x;
	shape->imaginary = 0 + shape_factor.y;
	return ;
}

void	fractal_polynomial_create(t_image_data *image_data,
												t_fractal_data *fractal_data)
{
	unsigned int		color;
	t_yx_value			pixel_position;
	int					i;

	pixel_position.y = -1;
	while (++pixel_position.y < fractal_data->fractal_size.y)
	{
		pixel_position.x = -1;
		while (++pixel_position.x < fractal_data->fractal_size.x)
		{
			set_new_values(fractal_data, &pixel_position);
			i = iterate_new_values(fractal_data, MAX_ITERATIONS);
			color = set_color(i, MAX_ITERATIONS);
			image_pixel_set(image_data->pixels_start_prt,
				image_data->pixels_per_line, &pixel_position, color);
		}
	}
	return ;
}

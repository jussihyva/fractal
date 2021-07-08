/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:53:49 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/08 12:03:02 by jkauppi          ###   ########.fr       */
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

void	update_offset_values_mandelbrot(t_yx_value_double *offset,
										t_yx_value *window_size, int y, int x)
{
	t_yx_value_double	offset_factor;

	offset_factor.y = (double)(window_size->y / 2 - y) / (window_size->y / 2)
		* 1.0;
	offset_factor.x = (double)(window_size->x / 2 - x) / (window_size->x / 2)
		* 1.0;
	offset->y = offset_factor.y;
	offset->x = offset_factor.x;
	return ;
}

static void	set_shape_values(t_fractal_data *fractal_data,
													t_yx_value *pixel_position)
{
	t_fractal_shape		*shape;
	t_yx_value			*fractal_size;

	shape = &fractal_data->shape;
	fractal_size = &fractal_data->fractal_size;
	shape->real = 2 * (pixel_position->x - fractal_size->x / 2)
		/ (0.5 * fractal_data->zoom * fractal_size->x) + fractal_data->offset.x;
	shape->imaginary = 2 * (pixel_position->y - fractal_size->y / 2)
		/ (0.5 * fractal_data->zoom * fractal_size->y) + fractal_data->offset.y;
	return ;
}

void	fractal_mandelbrot_create(t_image_data *image_data,
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
			set_shape_values(fractal_data, &pixel_position);
			set_new_values(fractal_data, &pixel_position);
			i = iterate_new_values(fractal_data, MAX_ITERATIONS);
			color = set_color(i, fractal_data->zoom);
			image_pixel_set(image_data->pixels_start_prt,
				image_data->pixels_per_line, &pixel_position, color);
		}
	}
	return ;
}

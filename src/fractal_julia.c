/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:00:13 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/29 19:23:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_something(t_image_data *image_data, t_yx_value *pixel_position)
{
	int					y_end_point;
	unsigned int		color;

	color = 0x00FF0000;
	y_end_point = pixel_position->y + 55;
	while (pixel_position->y < y_end_point)
	{
		image_pixel_set(image_data->pixels_start_prt,
			image_data->pixels_per_line, pixel_position, color);
		pixel_position->y++;
	}
	return ;
}

void	fractal_julia_create(t_image_data *image_data)
{
	t_fractal_data		fractal_data;
	unsigned int		color;
	int					max_iterations;
	t_yx_value			pixel_position;
	t_yx_value			image_size;
	int					i;

	ft_bzero(&fractal_data, sizeof(fractal_data));
	max_iterations = 300;
	image_size.y = 600;
	image_size.x = 900;
	fractal_data.zoom = 1;
	fractal_data.offset.y = 0;
	fractal_data.offset.x = 0.5;
	fractal_data.shape_real = -0.7;
	fractal_data.shape_imaginary = 0.27015;
	pixel_position.y = -1;
	while (++pixel_position.y < image_size.y)
	{
		pixel_position.x = -1;
		while (++pixel_position.x < image_size.x)
		{
			fractal_data.real = 1.5 * (pixel_position.x - image_size.x / 2)
				/ (0.5 * fractal_data.zoom * image_size.x)
				+ fractal_data.offset.x;
			fractal_data.imaginary = (pixel_position.y - image_size.y / 2)
				/ (0.5 * fractal_data.zoom * image_size.y)
				+ fractal_data.offset.y;
			i = 0;
			while (i++ < max_iterations)
			{
				fractal_data.real_prev = fractal_data.real;
				fractal_data.imaginary_prev = fractal_data.imaginary;
				fractal_data.real
					= (fractal_data.real_prev * fractal_data.real_prev)
					- (fractal_data.imaginary_prev
						* fractal_data.imaginary_prev)
					+ fractal_data.shape_real;
				fractal_data.imaginary
					= 2 * fractal_data.real_prev * fractal_data.imaginary_prev
					+ fractal_data.shape_imaginary;
				if (((fractal_data.real * fractal_data.real)
						+ (fractal_data.imaginary
							* fractal_data.imaginary)) > 4)
					break ;
			}
			color = (i % 256) << 0;
			color += 255 << 8;
			color += (255 * (i < max_iterations)) << 16;
			image_pixel_set(image_data->pixels_start_prt,
				image_data->pixels_per_line, &pixel_position, color);
		}
	}
	return ;
}

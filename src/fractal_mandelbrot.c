/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:53:49 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/06 12:29:26 by jkauppi          ###   ########.fr       */
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

static int	iterate_new_values(t_fractal_data *fractal_data, int max_iterations)
{
	int			num_of_iterations;
	double		distance_from_origin;

	num_of_iterations = 0;
	distance_from_origin = 0;
	while (num_of_iterations++ < max_iterations && distance_from_origin <= 4)
	{
		ft_memcpy(&fractal_data->prev, &fractal_data->new,
			sizeof(fractal_data->prev));
		update_new_values(fractal_data);
		distance_from_origin
			= calculate_distance_from_origin(&fractal_data->new);
	}
	return (num_of_iterations);
}

static void	update_shape_values(t_fractal_data *fractal_data,
													t_yx_value *pixel_position)
{
	fractal_data->shape_real = 2 * (pixel_position->x - fractal_data->fractal_size.x / 2)
		/ (0.5 * fractal_data->zoom * fractal_data->fractal_size.x) + fractal_data->offset.x;
	fractal_data->shape_imaginary = 2 * (pixel_position->y - fractal_data->fractal_size.y / 2)
		/ (0.5 * fractal_data->zoom * fractal_data->fractal_size.y) + fractal_data->offset.y;
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
			update_shape_values(fractal_data, &pixel_position);
			set_new_values(fractal_data, &pixel_position);
			i = iterate_new_values(fractal_data, MAX_ITERATIONS);
			color = set_color(i, MAX_ITERATIONS);
			image_pixel_set(image_data->pixels_start_prt,
				image_data->pixels_per_line, &pixel_position, color);
		}
	}
	return ;
}

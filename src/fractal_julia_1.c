/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_julia_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:00:13 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/06 00:09:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static unsigned int	set_color(int i, int max_iterations)
{
	unsigned int		color;

	color = (i % 256) << 16;
	color += 255 << 8;
	if (i < max_iterations)
		color += 188;
	else
		color += (255 * (i < max_iterations)) << 0;
	return (color);
}

static void	set_new_values(t_fractal_data *fractal_data,
							t_yx_value *pixel_position)
{
	t_yx_value		*image_size;

	image_size = &fractal_data->fractal_size;
	fractal_data->new.real = 1.5 * (pixel_position->x - image_size->x / 2)
		/ (0.5 * fractal_data->zoom * image_size->x) + fractal_data->offset.x;
	fractal_data->new.imaginary = (pixel_position->y - image_size->y / 2)
		/ (0.5 * fractal_data->zoom * image_size->y) + fractal_data->offset.y;
	return ;
}

static double	calculate_distance_from_origin(t_fractal_coordinates *new)
{
	double		distance_from_origin;

	distance_from_origin = (new->real * new->real)
		+ (new->imaginary * new->imaginary);
	return (distance_from_origin);
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

void	fractal_julia_create(t_image_data *image_data,
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

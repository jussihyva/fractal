/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 12:08:31 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/06 12:50:05 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	calculate_real_value(t_fractal_coordinate *prev,
															double shape_real)
{
	double	real;

	real = (prev->real * prev->real) - (prev->imaginary * prev->imaginary)
		+ shape_real;
	return (real);
}

static double	calculate_imaginary_value(t_fractal_coordinate *prev,
														double shape_imaginary)
{
	double	imaginary;

	imaginary = 2 * prev->real * prev->imaginary + shape_imaginary;
	return (imaginary);
}

void	update_new_values(t_fractal_data *fractal_data)
{
	fractal_data->new.real = calculate_real_value(&fractal_data->prev,
			fractal_data->shape.real);
	fractal_data->new.imaginary = calculate_imaginary_value(&fractal_data->prev,
			fractal_data->shape.imaginary);
	return ;
}

int	iterate_new_values(t_fractal_data *fractal_data, int max_iterations)
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

double	calculate_distance_from_origin(t_fractal_coordinate *new)
{
	double		distance_from_origin;

	distance_from_origin = (new->real * new->real)
		+ (new->imaginary * new->imaginary);
	return (distance_from_origin);
}

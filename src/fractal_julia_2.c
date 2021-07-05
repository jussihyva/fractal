/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_julia_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 23:49:19 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/05 23:50:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	calculate_real_value(t_fractal_coordinates *prev,
															double shape_real)
{
	double	real;

	real = (prev->real * prev->real) - (prev->imaginary * prev->imaginary)
		+ shape_real;
	return (real);
}

static double	calculate_imaginary_value(t_fractal_coordinates *prev,
														double shape_imaginary)
{
	double	imaginary;

	imaginary = 2 * prev->real * prev->imaginary + shape_imaginary;
	return (imaginary);
}

void	update_new_values(t_fractal_data *fractal_data)
{
	fractal_data->new.real = calculate_real_value(&fractal_data->prev,
			fractal_data->shape_real);
	fractal_data->new.imaginary = calculate_imaginary_value(&fractal_data->prev,
			fractal_data->shape_imaginary);
	return ;
}

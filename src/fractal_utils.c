/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 12:08:31 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/06 12:08:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	calculate_distance_from_origin(t_fractal_coordinates *new)
{
	double		distance_from_origin;

	distance_from_origin = (new->real * new->real)
		+ (new->imaginary * new->imaginary);
	return (distance_from_origin);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:58:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/06 11:59:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	set_color(int i, int max_iterations)
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

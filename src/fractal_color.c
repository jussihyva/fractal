/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:58:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/08 12:07:37 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	set_color(int i, double zoom)
{
	unsigned int		color;

	color = (i % 256) << 16;
	if (i < MAX_ITERATIONS)
		color += (255 - ((int)((zoom - 1) * 40)) % 256) << 8;
	else
		color += (255 - 0) << 8;
	if (i < MAX_ITERATIONS)
		color += 188;
	else
		color += (255 * (i < MAX_ITERATIONS)) << 0;
	return (color);
}

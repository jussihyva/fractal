/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 17:59:16 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/29 18:04:05 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_image_data	*get_image_data(void *image)
{
	t_image_data	*image_data;

	image_data = (t_image_data *)ft_memalloc(sizeof(*image_data));
	image_data->pixels_start_prt = (unsigned int *)mlx_get_data_addr(image,
			&image_data->bits_per_pixel,
			&image_data->size_line, &image_data->endian);
	image_data->pixels_per_line
		= (int)(image_data->size_line / (image_data->bits_per_pixel / 8));
	return (image_data);
}

void	image_pixel_set(unsigned int *pixels_start_prt, int pixels_per_line,
						t_yx_value *pixel_position, unsigned int pixel_color)
{
	unsigned int		*pixel_ptr;

	pixel_ptr = pixels_start_prt + (pixels_per_line * pixel_position->y)
		+ pixel_position->x;
	*pixel_ptr = pixel_color;
	return ;
}

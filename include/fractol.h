/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:16:47 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/06 09:52:32 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"

# define ESC				53
# define MAX_ITERATIONS		300

typedef enum e_window_action
{
	NO_ACTION,
	UPDATE_ONGOING,
	UPDATE_IMAGE
}				t_window_action;

typedef struct s_yx_value
{
	int		y;
	int		x;
}				t_yx_value;

typedef struct s_yx_value_double
{
	double	y;
	double	x;
}				t_yx_value_double;

typedef struct s_fractal_coordinates
{
	double				real;
	double				imaginary;
}				t_fractal_coordinates;

typedef struct s_image_data
{
	unsigned int	*pixels_start_prt;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				pixels_per_line;
}				t_image_data;

typedef struct s_fractal_data
{
	double					shape_real;
	double					shape_imaginary;
	t_fractal_coordinates	new;
	t_fractal_coordinates	prev;
	t_yx_value_double		offset;
	t_yx_value				fractal_size;
	double					zoom;
}				t_fractal_data;

typedef struct s_window
{
	void				*mlx;
	void				*win;
	t_window_action		window_action;
	t_yx_value			window_size;
	void				*image;
	t_image_data		*image_data;
	int					image_status;
	t_fractal_data		*fractal_data;
}				t_window;

t_window		*window_initialize(char *window_name);
int				window_close(t_window *window);
int				mouse_button_press(int keycode, int x, int y, t_window *window);
int				mouse_motion_notify(int x, int y, t_window *window);
int				keyboard_key_press(int keycode, t_window *window);
void			window_release(t_window **window);
void			image_pixel_set(unsigned int *pixels_start_prt,
					int pixels_per_line, t_yx_value *pixel_position,
					unsigned int pixel_color);
t_image_data	*get_image_data(void *image);
void			fractal_julia_create(t_image_data *image_data,
					t_fractal_data *fractal_data);
void			update_new_values(t_fractal_data *fractal_data);

#endif

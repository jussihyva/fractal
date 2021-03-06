/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:16:47 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/08 12:02:40 by jkauppi          ###   ########.fr       */
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
	E_NO_ACTION,
	E_UPDATE_ONGOING,
	E_UPDATE_IMAGE
}				t_window_action;

typedef enum e_type_of_fractal
{
	E_JULIA,
	E_MANDELBROT,
	E_POLYNOMIAL
}				t_type_of_fractal;

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

typedef struct s_cmd_args
{
	int				argc;
	char			**argv;
	char			*fractal;
}				t_cmd_args;

typedef struct s_fractal_shape
{
	double				real;
	double				imaginary;
}				t_fractal_shape;

typedef struct s_fractal_coordinate
{
	double				real;
	double				imaginary;
}				t_fractal_coordinate;

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
	t_type_of_fractal		type_of_fractal;
	t_fractal_shape			shape;
	t_fractal_coordinate	new;
	t_fractal_coordinate	prev;
	t_yx_value_double		offset;
	t_yx_value				fractal_size;
	double					zoom;
}				t_fractal_data;

typedef void	(t_dfsdfdsf);

typedef t_dfsdfdsf(*t_save_cmd_argument)(t_cmd_args *cmd_args, char opt,
																char *next_arg);

typedef t_cmd_args*(*t_initialize_cmd_args)(int argc, char **argv);

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

typedef struct s_arg_parser_functions
{
	t_initialize_cmd_args	initialize_cmd_args;
	t_save_cmd_argument		save_cmd_argument;
}				t_arg_parser_functions;

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
unsigned int	set_color(int i, double zoom);
void			fractal_julia_create(t_image_data *image_data,
					t_fractal_data *fractal_data);
void			fractal_mandelbrot_create(t_image_data *image_data,
					t_fractal_data *fractal_data);
void			fractal_polynomial_create(t_image_data *image_data,
					t_fractal_data *fractal_data);
double			calculate_distance_from_origin(t_fractal_coordinate *new);
int				iterate_new_values(t_fractal_data *fractal_data,
					int max_iterations);
void			update_new_values(t_fractal_data *fractal_data);
t_cmd_args		*ft_arg_parser(t_arg_parser_functions *arg_parser_functions,
					int argc, char **argv, char *options);
void			print_usage(void);
t_fractal_data	*fractal_initialize(char *fractal, t_yx_value *window_size);
void			update_shape_values(t_fractal_data *fractal_data,
					t_yx_value *window_size, int x, int y);
void			update_shape_values_julia(t_fractal_shape *shape,
					t_yx_value *window_size, int y, int x);
void			update_shape_values_polynomial(t_fractal_shape *shape,
					t_yx_value *window_size, int y, int x);
void			update_offset_values_mandelbrot(t_yx_value_double *offset,
					t_yx_value *window_size, int y, int x);

#endif

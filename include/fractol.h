/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:16:47 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/29 16:16:04 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"

# define ESC		53

typedef struct s_yx_value
{
	int		y;
	int		x;
}				t_yx_value;

typedef struct s_image_data
{
	char			*pixels_start_prt;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				pixels_per_line;
}				t_image_data;

typedef struct s_window
{
	void			*mlx;
	void			*win;
	int				window_action;
	t_yx_value		window_size;
	void			*image;
	t_image_data	*image_data;
	int				image_status;
}				t_window;

t_window	*window_initialize(char *window_name);
int			window_close(t_window *window);
int			mouse_button_press(int keycode, int x, int y, t_window *window);
int			mouse_motion_notify(int x, int y, t_window *window);
int			keyboard_key_press(int keycode, t_window *window);
void		window_release(t_window **window);

#endif

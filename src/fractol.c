/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:16:38 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/08 11:45:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_usage(void)
{
	ft_printf("Usage:\n");
	ft_printf("  ./fractol -F <type_of_fractal>\n");
	ft_printf("\n\n Example:   ./fractol -F j\n");
	ft_printf("\n\nMandatory parameter:\n");
	ft_printf("  -F <type_of_fractal>\n");
	ft_printf("Optional parameter:\n");
	ft_printf("  -h    Help printout\n");
	ft_printf("\n\n   <type_of_fractal>\n");
	ft_printf("  j     Julia      (z = z^2 + C.");
	ft_printf(" C = Constant values + mouse locaation on the image.)\n");
	ft_printf("  m     Mandelbrot (z = z^2 + C.");
	ft_printf(" C = Mouse Distance from the origin of the image.)\n");
	ft_printf("  p     Polynomial (z = z^2 - C.");
	ft_printf(" C = 1 + mouse locaation on the image.)\n");
	exit(42);
}

static t_cmd_args	*initialize_cmd_args(int argc, char **argv)
{
	t_cmd_args			*cmd_args;

	cmd_args = (t_cmd_args *)ft_memalloc(sizeof(*cmd_args));
	cmd_args->argc = argc;
	cmd_args->argv = argv;
	cmd_args->fractal = ft_strdup("j");
	return (cmd_args);
}

static void	save_cmd_argument(t_cmd_args *cmd_args, char opt, char *next_arg)
{
	if (opt == 'F')
	{
		ft_strdel(&cmd_args->fractal);
		cmd_args->fractal = ft_strdup(next_arg);
	}
	else if (opt == 'h')
		print_usage();
	return ;
}

int	main(int argc, char **argv)
{
	t_window					*window;
	t_cmd_args					*cmd_args;
	char						*options;
	t_arg_parser_functions		arg_parser_functions;

	if (argc == 1)
		print_usage();
	options = ft_strdup("hF:");
	arg_parser_functions.initialize_cmd_args = initialize_cmd_args;
	arg_parser_functions.save_cmd_argument = save_cmd_argument;
	cmd_args = ft_arg_parser(&arg_parser_functions, argc, argv, options);
	window = window_initialize(cmd_args->fractal);
	window->image = mlx_new_image(window->mlx, window->window_size.x,
			window->window_size.y);
	window->image_status = 0;
	window->image_data = get_image_data(window->image);
	update_shape_values(window->fractal_data, &window->window_size, 0, 0);
	window->window_action = E_UPDATE_IMAGE;
	mlx_loop(window->mlx);
	ft_memdel((void **)&cmd_args->fractal);
	ft_memdel((void **)&cmd_args);
	window_release(&window);
	return (0);
}

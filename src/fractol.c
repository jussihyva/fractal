/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:16:38 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/07 18:17:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_usage(void)
{
	ft_printf("Usage:\n");
	ft_printf("1.     ./bin/n_puzzle [options]\n");
	ft_printf("      3\n");
	ft_printf("      1 2 3\n");
	ft_printf("      4 5 6\n");
	ft_printf("      8 7 0\n");
	ft_printf("      <Cntrl>-D\n");
	ft_printf("\n2.     cat data/3_3_05.map | ./bin/n_puzzle [options]\n");
	ft_printf("%s %s\n",
		"\n3.     python ./bin/PuzzleGenerator.py -s 3",
		"| ./bin/n_puzzle [options]");
	ft_printf("%s %s\n",
		"\n4.     python ./bin/PuzzleGenerator.py -s 3",
		"| ./bin/n_puzzle -D 2000 | ./bin/n-puzzle_gui.py\n");
	ft_printf("\n\nOptional parameters:\n");
	ft_printf("  -A <alg_name> Puzzle solving algorithm\n");
	ft_printf("  -H <alg_name> Heuristic algorithm for distance calculation\n");
	ft_printf("  -L    Event logging level\n");
	ft_printf("  -D    Result printout speed. Delay (ms) between tile moves\n");
	ft_printf("  -r    Release request for post proocessing functions\n");
	ft_printf("  -h    Help printout\n");
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

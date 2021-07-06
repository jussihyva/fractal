/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:32:50 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/06 13:44:05 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_usage(void)
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
	print_alg_alternatives();
	exit(42);
}

void	save_cmd_arguments(t_cmd_args *cmd_args, char opt, char *next_arg)
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

static void	split_cmd_argument(void (fn)(t_cmd_args *, char, char *),
							t_cmd_args *cmd_args, int *arg_index, char *options)
{
	int			i;
	char		*arg;
	char		*opt_ptr;

	arg = cmd_args->argv[*arg_index];
	i = 1;
	while (arg[i])
	{
		opt_ptr = ft_strchr(options, arg[i]);
		if (opt_ptr)
		{
			if (*(opt_ptr + 1) == ':')
			{
				if (++(*arg_index) >= cmd_args->argc)
					param_error("Missing argument for parameter: -%c", arg[i]);
				fn(cmd_args, arg[i], cmd_args->argv[*arg_index]);
				break ;
			}
			else
				fn(cmd_args, arg[i], NULL);
			i++;
		}
		else
			param_error("Unknown parameter: -%c", arg[i]);
	}
}

t_cmd_args	*arg_parser(void (fn)(t_cmd_args *, char, char *), int argc,
													char **argv, char *options)
{
	t_cmd_args			*cmd_args;
	int					arg_index;

	cmd_args = initialize_cmd_args(argc, argv);
	arg_index = 0;
	while (++arg_index < argc)
	{
		if (argv[arg_index][0] == '-')
			split_cmd_argument(fn, cmd_args, &arg_index, options);
		else
			print_usage();
	}
	return (cmd_args);
}

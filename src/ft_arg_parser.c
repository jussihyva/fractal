/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:32:50 by jkauppi           #+#    #+#             */
/*   Updated: 2021/07/07 11:49:10 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	param_error(const char *error_string, const char s)
{
	ft_printf(error_string, s);
	ft_printf("\n");
	exit(42);
	return ;
}

static void	split_cmd_argument(t_save_cmd_argument save_cmd_arguments,
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
				save_cmd_arguments(cmd_args, arg[i],
					cmd_args->argv[*arg_index]);
				break ;
			}
			else
				save_cmd_arguments(cmd_args, arg[i], NULL);
			i++;
		}
		else
			param_error("Unknown parameter: -%c", arg[i]);
	}
}

t_cmd_args	*ft_arg_parser(t_arg_parser_functions *arg_parser_functions,
										int argc, char **argv, char *options)
{
	t_cmd_args				*cmd_args;
	int						arg_index;
	t_initialize_cmd_args	initialize_cmd_args;
	t_save_cmd_argument		save_cmd_argument;

	initialize_cmd_args = arg_parser_functions->initialize_cmd_args;
	save_cmd_argument = arg_parser_functions->save_cmd_argument;
	cmd_args = initialize_cmd_args(argc, argv);
	arg_index = 0;
	while (++arg_index < argc)
	{
		if (argv[arg_index][0] == '-' && ft_strlen(argv[arg_index]) > 1)
			split_cmd_argument(save_cmd_argument, cmd_args, &arg_index,
				options);
		else
			print_usage();
	}
	return (cmd_args);
}

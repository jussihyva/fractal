# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/28 16:20:48 by jkauppi           #+#    #+#              #
#    Updated: 2021/07/08 11:13:12 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS				=	$(shell uname -s)

A_FILES				=	libft/libft.a libft_printf/libftprintf.a
H_FILES				=	libft/libft.h libft_printf/include/ft_printf.h

LIB_FOLDERS			=	$(dir $(A_FILES))

.PHONY: all
all: h_files $(A_FILES) libraries

$(A_FILES):
	ar -rcs $@ Makefile
	ar -d $@ Makefile

.PHONY: h_files
h_files: $(H_FILES)
	@cp -f $^ ./

.PHONY: libraries
libraries:
	for folder in $(LIB_FOLDERS) ; do \
	    make -C $$folder ; \
	done

.PHONY: clean
clean:
	for folder in $(LIB_FOLDERS) ; do \
	    make -C $$folder clean ; \
	done
	rm -f $(notdir $(H_FILES))
	rm -f $(notdir $(A_FILES))

.PHONY: fclean
fclean:
	for folder in $(LIB_FOLDERS) ; do \
		make -C $$folder fclean ; \
	done
	rm -f $(notdir $(H_FILES))
	rm -f $(notdir $(A_FILES))

.PHONY: re
re: all
	for folder in $(LIB_FOLDERS) ; do \
	    make -C $$folder re ; \
	done

.PHONY: norm
norm:
	for folder in $(LIB_FOLDERS) ; do \
	    make -C $$folder norm ; \
	done

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/28 15:02:24 by jkauppi           #+#    #+#              #
#    Updated: 2021/07/08 11:05:06 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Input parameters

OS					=	$(shell uname -s)
CUR_DIR				=	$(abspath .)

ifdef F
	FRACTAL			=	-F $(F)
else
	FRACTAL			=	-F j
endif

# Application specific parameters
NAME			=	fractol
NAMES			=	$(NAME)

# Folders
LIB				=	lib
BIN				=	.
DATA			=	data
OBJ				=	obj
SRC				=	src
INCLUDE			=	include
TEST			=	test
FOLDERS			=	$(LIB) $(BIN) $(DATA) $(OBJ) $(SRC) $(INCLUDE) $(TEST)
INCLUDES		=	-I $(INCLUDE) -I $(LIB)

# C (Source code) and H (Header) files
SRC_C_FILES		=	event_mouse.c event_keyboard.c window.c image.c \
					fractal_utils_1.c fractal_utils_2.c fractal_color.c \
					fractal_julia.c \
					fractal_mandelbrot.c \
					fractal_polynomial.c \
					ft_arg_parser.c
SRC_H_FILES		=	fractol.h
LOCAL_LIBS		=	libftprintf.a libft.a
GLOBAL_LIBS		=	libmlx.a
ifneq ($(OS), Darwin)
	GLOBAL_LIBS	+=	libX11.a libXext.a
endif
LOCAL_LIB_FILES	=	$(addprefix $(LIB)/, $(LOCAL_LIBS))
LIB_FILES		=	$(addprefix -l , $(patsubst lib%.a, %, $(LOCAL_LIBS)))
LIB_FILES		+=	$(addprefix -l , $(patsubst lib%.a, %, $(GLOBAL_LIBS)))

# Path folders for H, C, O and APP files
H_FILES			=	$(addprefix $(INCLUDE)/, $(SRC_H_FILES))
C_FILES			=	$(addprefix $(SRC)/, $(SRC_C_FILES))
O_FILES			=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_C_FILES)))
APP_FILES		=	$(addprefix $(BIN)/, $(NAMES))

# Compiler and linking parameters
CC				=	clang
C_FLAGS			=	-g -Wall -Wextra -Werror $(INCLUDES)
LD_FLAGS		=	-std=gnu17 -L$(LIB) $(LIB_FILES)

ifeq ($(OS), Darwin)
	FRAMEWORKS		=	-framework OpenGL -framework AppKit
	D_ATTRIBUTES	=	
	INCLUDES		+=	-I $(HOME)/.brew/include
	LD_FLAGS		+=	$(FRAMEWORKS)
else
	D_ATTRIBUTES	=	
	LD_FLAGS		+=	
endif
LD_FLAGS			+=	$(D_ATTRIBUTES)

# Colours for printouts
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
END				=	\033[0m

.PHONY: all
all: $(FOLDERS) $(H_FILES) $(C_FILES) libraries $(APP_FILES)
	@echo "$(GREEN)Done!$(END)"

$(APP_FILES): $(BIN)/%: $(SRC)/%.c $(H_FILES) $(O_FILES) Makefile
	$(CC) -o $@ $< $(O_FILES) $(LD_FLAGS) $(C_FLAGS)

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c $(H_FILES) Makefile $(LOCAL_LIB_FILES)
	$(CC) -c -o $@ $< $(C_FLAGS) $(D_ATTRIBUTES)

$(FOLDERS):
	mkdir $@

$(C_FILES):
	touch $@

$(H_FILES):
	touch $@

.PHONY: libraries
libraries:
	@make -C ${LIB}

.PHONY: libraries_re
libraries_re:
	@make -C ${LIB} re

.PHONY: libraries_norm
libraries_norm:
	-@make -C ${LIB} norm

.PHONY: run
run: all
ifeq ($(OS), Darwin)
	$(CUR_DIR)/$(BIN)/$(NAME) $(FRACTAL)
else
	valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all \
	$(CUR_DIR)/$(BIN)/$(NAME) $(FRACTAL)
endif

.PHONY: run_leaks
run_leaks: all
ifeq ($(OS), Darwin)
	leaks $(NAME)
else
	valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all \
	$(CUR_DIR)/$(BIN)/$(NAME) $(FRACTAL)
endif

.PHONY: clean
clean:
	@make -C ${LIB} clean
	rm -f $(O_FILES)

.PHONY: fclean
fclean: clean
	@make -C ${LIB} fclean
	rm -f $(BIN)/$(NAME)

.PHONY: re
re: fclean all

.PHONY: norm
norm: libraries_norm
ifeq ($(OS), Darwin)
	norminette-beta $(SRC)/* $(INCLUDE)/*
else
	norminette $(SRC)/* $(INCLUDE)/*
endif

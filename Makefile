# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/28 15:02:24 by jkauppi           #+#    #+#              #
#    Updated: 2021/06/29 23:11:38 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Input parameters

OS					=	$(shell uname -s)
CUR_DIR				=	$(abspath .)

ifdef M
	MAX_MOVES		=	-i $(M)
else
	MAX_MOVES		=	-i 10
endif

ifdef G
	ifeq (1, $(G))
		PUZZLE_GUI	=	>/dev/null
	else
		PUZZLE_GUI	=	| ./bin/n-puzzle_gui.py
	endif
else
	PUZZLE_GUI		=
endif

ifdef S
	PUZZLE_SIZE		=	$(S)
else
	PUZZLE_SIZE		=	3
endif

ifdef D
	PRINT_DELAY		=	$(D)
else
	PRINT_DELAY		=	0
endif

ifdef F
	MAP_FILE		=	$(F)
else
	MAP_FILE		=	data/3_3_05.map
endif

ifdef L
	LOGING_LEVEL	=	-L $(L)
else
	LOGING_LEVEL	=
endif

ifdef A
	ALGORITHM	=	$(A)
else
	ALGORITHM	=	greedy
endif

ifdef H
	HEURISTIC	=	-H $(H)
else
	HEURISTIC	=	-H t
endif

# Application specific parameters
NAME			=	fractol
NAMES			=	$(NAME)

# Folders
LIB				=	lib
BIN				=	bin
DATA			=	data
OBJ				=	obj
SRC				=	src
INCLUDE			=	include
TEST			=	test
FOLDERS			=	$(LIB) $(BIN) $(DATA) $(OBJ) $(SRC) $(INCLUDE) $(TEST)
INCLUDES		=	-I $(INCLUDE) -I $(LIB)

# C (Source code) and H (Header) files
SRC_C_FILES		=	event_mouse.c event_keyboard.c window.c image.c \
					fractal_julia.c
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
	cat $(CUR_DIR)/$(MAP_FILE) \
	| $(CUR_DIR)/$(BIN)/$(NAME) $(LOGING_LEVEL) -A $(ALGORITHM) $(HEURISTIC) -D $(PRINT_DELAY) $(PUZZLE_GUI)
else
	cat $(CUR_DIR)/$(MAP_FILE) | valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all \
	$(CUR_DIR)/$(BIN)/$(NAME) $(LOGING_LEVEL) -A $(ALGORITHM) $(HEURISTIC) -D $(PRINT_DELAY) $(PUZZLE_GUI)
endif

.PHONY: run_loop
run_loop: all
ifeq ($(OS), Darwin)
	while [ 1 -eq 1 ] ; do \
		python $(CUR_DIR)/bin/PuzzleGenerator.py ${MAX_MOVES} -s $(PUZZLE_SIZE) \
		| $(CUR_DIR)/$(BIN)/$(NAME) $(LOGING_LEVEL) -rA $(ALGORITHM) $(HEURISTIC) -D $(PRINT_DELAY) $(PUZZLE_GUI) ; \
		done
else
	while [ 1 -eq 1 ] ; do \
		$(CUR_DIR)/bin/PuzzleGenerator.py ${MAX_MOVES} -s $(PUZZLE_SIZE) \
		| $(CUR_DIR)/$(BIN)/$(NAME) $(LOGING_LEVEL) -rA $(ALGORITHM) $(HEURISTIC) -D $(PRINT_DELAY) $(PUZZLE_GUI) ; \
		done
endif

.PHONY: run_test
run_test: all
	while [ 1 -eq 1 ] ; \
	do \
		python3 $(CUR_DIR)/test/n-puzzle_test.py $(PUZZLE_SIZE) ; \
	done

.PHONY: run_leaks
run_leaks: all
ifeq ($(OS), Darwin)
	cat $(CUR_DIR)/$(MAP_FILE) | $(CUR_DIR)/$(BIN)/$(NAME) $(LOGING_LEVEL) -A $(ALGORITHM) $(HEURISTIC) -D $(PRINT_DELAY) $(PUZZLE_GUI)
else
	cat $(CUR_DIR)/$(MAP_FILE) | valgrind -s --tool=memcheck \
	--leak-check=full --show-leak-kinds=all \
	$(CUR_DIR)/$(BIN)/$(NAME) $(LOGING_LEVEL) -A $(ALGORITHM) $(HEURISTIC) -D $(PRINT_DELAY) $(PUZZLE_GUI)
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

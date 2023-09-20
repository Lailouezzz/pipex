# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-boud <ale-boud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 23:28:51 by ale-boud          #+#    #+#              #
#    Updated: 2023/09/20 13:41:11 by ale-boud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---
# Tools
# ---

MKDIR := mkdir
RM := rm -f

# ---
# Build variables
# ---

# Compiler

CC := gcc

CWARN := all extra
CWARN := $(CWARN:%=-W%)

CFLAGS := $(CWARN) -g3

# Preprocessor flag

CPPFLAGS := -I./libft -I.

# Linker

LD := gcc
LDLIBS := 
LIBS := libft/libft.a
LDFLAGS := -Llibft

# ---
# Lib information
# ---

NAME := pipex

SRC_DIR := ./
SRCS := pipex.c utils.c main.c destroy.c init.c error.c exec.c

SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJ_DIR := ./build
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

SRCS_BONUS := 
SRCS_BONUS := $(SRCS_BONUS:%=$(SRC_DIR)/%)
OBJS_BONUS := $(SRCS_BONUS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ---
#  General targets
# ---

# Build everything

all: $(NAME)

bonus: all

# Mostly clean (clean everything without the end result)

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) clean -C libft

# Clean everything

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft

# Rebuild

re: clean all

# Bonus

bonus: all
	
.PHONY: all clean fclean re bonus

# ---
# Build targets
# ---

libft/libft.a:
	$(MAKE) -C libft all

$(NAME): $(OBJS) $(LIBS)
	$(LD) $^ -o $@ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

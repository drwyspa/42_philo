# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pjedrycz <p.jedryczkowski@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 21:09:23 by pjedrycz          #+#    #+#              #
#    Updated: 2024/10/24 21:29:25 by pjedrycz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= gcc
CFLAGS		= -Werror -Wextra -Wall -pthread

# Run 'make re MODE=pretty' for color formatting.
# Run 'make re MODE=debug' for debug formatting.
MODE		= none
ifeq ($(MODE), pretty)
	CFLAGS += -D DEBUG_FORMATTING=1
endif
ifeq ($(MODE), debug)
	CFLAGS += -D DEBUG_FORMATTING=1 -fsanitize=thread -g
endif

SRC_PATH	= src/
OBJ_PATH	= obj/

SRC			=	exit.c \
				init.c \
				main.c \
				output.c \
				parsing.c \
				philo_control.c \
				philosopher.c \
				time.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

INC			= -I ./includes/

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seongjki <seongjk@student.42seoul.kr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/25 10:47:05 by seongjki          #+#    #+#              #
#    Updated: 2021/09/27 15:12:32 by seongjki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SVR = server
SVR_DIR = ./server_src/
SVR_SRC_NAME = server.c
SVR_BONUS_SRC_NAME = server_bonus.c
SVR_SRC = $(addprefix $(SVR_DIR),$(SVR_SRC_NAME))
SVR_BONUS_SRC = $(addprefix $(SVR_DIR),$(SVR_BONUS_SRC_NAME))

SVR_OBJ_NAME = $(SVR_SRC:.c=.o)
SVR_BONUS_OBJ_NAME = $(SVR_BONUS_SRC:.c=.o)
SVR_OBJ = $(SVR_OBJ_NAME)
SVR_BONUS_OBJ = $(SVR_BONUS_OBJ_NAME)

CLI = client
CLI_DIR = ./client_src/
CLI_SRC_NAME = client.c
CLI_BONUS_SRC_NAME = client_bonus.c
CLI_SRC = $(addprefix $(CLI_DIR),$(CLI_SRC_NAME))
CLI_BONUS_SRC = $(addprefix $(CLI_DIR),$(CLI_BONUS_SRC_NAME))

CLI_OBJ_NAME = $(CLI_SRC:.c=.o)
CLI_BONUS_OBJ_NAME = $(CLI_BONUS_SRC:.c=.o)
CLI_OBJ = $(CLI_OBJ_NAME)
CLI_BONUS_OBJ = $(CLI_BONUS_OBJ_NAME)

PRINTF_DIR = ./ft_printf/
PRINTF_NAME = ftprintf
PRINTF = $(PRINTF_DIR)lib$(PRINTF_NAME).a

NAME = $(SVR) $(CLI)
IS_BONUS = 0
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./include 

ifeq ($(IS_BONUS),1)
	SVR_OBJECTS = $(SVR_BONUS_OBJ)
	CLI_OBJECTS = $(CLI_BONUS_OBJ)
else
	SVR_OBJECTS = $(SVR_OBJ)
	CLI_OBJECTS = $(CLI_OBJ)
endif

all: $(NAME)

bonus:
	make IS_BONUS=1 all

$(NAME): $(PRINTF)

$(PRINTF):
	make -C $(PRINTF_DIR) all

$(SVR): $(SVR_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE) -L$(PRINTF_DIR) -l$(PRINTF_NAME) $< -o $@

$(CLI): $(CLI_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE) -L$(PRINTF_DIR) -l$(PRINTF_NAME) $< -o $@

$(SVR_OBJ): $(SVR_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(CLI_OBJ): $(CLI_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(SVR_BONUS_OBJ): $(SVR_BONUS_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(CLI_BONUS_OBJ): $(CLI_BONUS_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(SVR_OBJ) $(CLI_OBJ)
	rm -f $(SVR_BONUS_OBJ) $(CLI_BONUS_OBJ)
	make -C $(PRINTF_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

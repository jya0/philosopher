# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 16:18:33 by jyao              #+#    #+#              #
#    Updated: 2022/10/23 20:11:28 by jyao             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME := philo

SRCS := philo_main.c \
	philo_initialise.c	philo_atoi.c	philo_exit.c	philo_calloc.c	\
	philo_thread_routine.c	philo_action.c	philo_safe.c\
	philo_print_event.c

OBJS = $(SRCS:.c=.o)

CC := gcc

LIBS := -pthread

CFLAGS = -Wall -Wextra -Werror -g $(LIBS)

HEADER = philo.h

BONUS = ./philo_bonus

all: $(NAME) $(HEADER)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

bonus:
	make -C $(BONUS)

.PHONY: all clean fclean re

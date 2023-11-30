# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyao <jyao@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 16:18:33 by jyao              #+#    #+#              #
#    Updated: 2022/10/21 15:33:34 by jyao             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME := philo_bonus

SRCS := philo_main_bonus.c	philo_process_bonus.c	\
	philo_initialise_bonus.c	philo_atoi_bonus.c	philo_exit_bonus.c	philo_calloc_bonus.c	\
	philo_action_bonus.c	philo_safe_bonus.c	\
	philo_print_event_bonus.c	\
	philo_itoa_bonus.c	philo_strjoin_bonus.c	philo_usleep_bonus.c

OBJS = $(SRCS:.c=.o)

CC := gcc

LIBS := -pthread

CFLAGS = -Wall -Wextra -Werror -g $(LIBS)

HEADER = philo_bonus.h

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

.PHONY: all clean fclean re
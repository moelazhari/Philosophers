# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 19:50:01 by mazhari           #+#    #+#              #
#    Updated: 2022/04/10 20:10:39 by mazhari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
CFLAGS = -Wall -Werror -Wextra -g

NAME= ./philo/philo
NAME_B= ./philo_bonus/philo_bonus

INCLUDES= ./philo/includes
INCLUDES_B= ./philo_bonus/includes

HEDEAR= $(INCLUDES)/philo.h
HEDEAR_B= $(INCLUDES_B)/philo_bonus.h

ACTION= $(addprefix src/, $(addprefix actions/, philo))
INIT= $(addprefix src/, $(addprefix init/, data_init))
UTILS= $(addprefix src/, $(addprefix utils/, utils))

FILES= $(addprefix philo/, src/main $(ACTION) $(INIT) $(UTILS))
FILES_B= $(addprefix philo_bonus/, src/main $(ACTION) $(INIT) $(UTILS))

OBJS= $(FILES:=.o)
OBJS_B= $(FILES_B:=_bonus.o)

all: $(NAME)

bonus: $(NAME_B)

%_bonus.o: %_bonus.c $(HEDEAR_B)
	$(CC) -I$(INCLUDES_B) $(CFLAGS) -c $< -o $@

%.o: %.c $(HEDEAR)
	$(CC) -I$(INCLUDES) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEDEAR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(NAME_B): $(OBJS_B) $(HEDEAR_B)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(NAME_B)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_B)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_B)

re: fclean all

rebonus: fclean bonus

.PHONY: all bonus clean f re rebonus
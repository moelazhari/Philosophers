# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 19:50:01 by mazhari           #+#    #+#              #
#    Updated: 2022/04/06 02:59:37 by mazhari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= ./philo/philo
NAME_BONUS= ./philo_bonus/philo_bonus

HEADER= ./philo/philo.h

HEADER_BONUS= ./philo_bonus/philo_bonus.h

CC= gcc
CFLAGS = -Wall -Werror -Wextra

SRCS = 	./philo/main.c \
		./philo/data_init.c \
		./philo/philo.c \
		./philo/utils.c \

OBJS = $(SRCS:.c=.o)
	
SRCS_BONUS = 	./philo_bonus/main_bonus.c \
				./philo_bonus/data_init_bonus.c \
				./philo_bonus/philo_bonus.c \
				./philo_bonus/utils_bonus.c \

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)
	
%.o: %.c $(HEADER) $(HEADER_BONUS)
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(OBJS_BONUS) $(HEADER_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re rebonus
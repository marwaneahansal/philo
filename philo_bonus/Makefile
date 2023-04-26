# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/26 06:56:33 by mahansal          #+#    #+#              #
#    Updated: 2023/04/26 11:16:16 by mahansal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc

NAME 		= philo_bonus

SRCS 		= main.c ft_atoi.c helpers.c 

OBJS 		= $(SRCS:.c=.o)

CFLAGS 		= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME) -pthread 
	
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
 
re: fclean all
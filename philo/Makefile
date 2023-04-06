# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mahansal <mahansal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/01 23:48:55 by mahansal          #+#    #+#              #
#    Updated: 2023/04/06 20:53:58 by mahansal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc

NAME 		= philo

SRCS 		= main.c ft_atoi.c helpers.c threads.c

OBJS 		= $(SRCS:.c=.o)

CFLAGS 		= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread
	#  -g -fsanitize=address
	
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
 
re: fclean all
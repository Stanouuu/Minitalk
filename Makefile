# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 17:15:24 by yanthoma          #+#    #+#              #
#    Updated: 2022/10/12 16:44:00 by sbarrage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	server.c	client.c\

OBJS	= ${SRCS:.c=.o}

Bonus_OBJS = ${BONUS:.c=.o}

INCLUDES = -I ./Printf/ -I ./Libft/

LP = ./Printf/libftprintf.a ./Libft/libft.a

CC	= gcc

CFLAGS = -Wall -Wextra -Werror

all:	lib	server	client

lib:
	@make -C Libft/
	@make -C Printf/

relib:
	@make re -C Libft/
	@make re -C Printf/

.c.o:
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o ${<:.c=.o}

server: server.o
	$(CC) $(CFLAGS) -o $@ ${INCLUDES} $< ${LP}

client: client.o
	$(CC) $(CFLAGS) -o $@ ${INCLUDES} $< ${LP}

clean:
	rm -f ${OBJS}
	@make fclean -C Libft/
	@make fclean -C Printf/

fclean:	clean
	rm -f server client

re:			fclean all relib

.PHONY: all clean fclean re lib relib

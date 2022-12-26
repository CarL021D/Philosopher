# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: caboudar <caboudar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 15:12:48 by caboudar          #+#    #+#              #
#    Updated: 2022/12/26 19:24:57 by caboudar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosopher

SRCS	= 		srcs/philosopher.c 				\
				srcs/init.c						\
				srcs/check_errors.c				\
				srcs/thread_stop_handler.c		\
				srcs/philo_action.c 			\
				srcs/utils.c					\
				srcs/free.c						\

OBJS	= ${SRCS:.c=.o}

CFLAGS	= -Wall -Werror -Wextra -g

CC		= gcc

RM		= rm -f

INCS    = includes

all:	${NAME}

.c.o:
		@$(CC) ${CFLAGS} -I$(INCS) -c $< -o $@

${NAME}:	${OBJS}
		@${CC} ${CFLAGS} ${OBJS} -o philosopher
		@printf "%s\e[0;32m philosopher : Compiling object file into executable\n\e[0m" "-"

clean:
		@${RM} ${OBJS}
		@printf "%s\e[0;31m philosopher : Delete all object files\n\e[0m" "-"

fclean:
		@${RM} ${OBJS}
		@printf "%s\e[0;31m philosopher : Delete all object files\n\e[0m" "-"
		@${RM} ${NAME}
		@printf "%s\e[0;31m philosopher : Delete executable\n\e[0m" "-"

re: fclean ${NAME}

.PHONY: all clean fclean re
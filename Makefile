NAME = pipex

CC = gcc

FLAGS = #-Wall -Wextra -Werror

SRC	=	main.c		\
		parsing.c	\
		utils.c		\
		split.c		\

OBJS = ${SRC:.c=.o}

all:	${NAME}

${NAME}:${OBJS}
	 $(CC) $(FLAGS) -o $(NAME) $(OBJS)

%.o:	%.c
	${CC} ${FLAGS} -c $< -o $@

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re: fclean all

.PHONY: clean fclean re

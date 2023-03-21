SRCS	= main.c \
			constants.c \
			free.c \
			pipe_fork.c \
			param.c

OBJS 	= ${SRCS:.c=.o}

NAME 	= pipex

LIB		= libpipex.a

CC		= gcc

RM		= rm -f

AR		= ar rc

CFLAGS	= -Wextra -Wall -Werror

.c.o:	
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS}
				make bonus -C ./libft
				cp ./libft/libft.a ${LIB}
				${AR} ${LIB} ${OBJS}
				ranlib ${LIB}
			${CC} ${CFLAGS} -o ${NAME} main.c -L. -lpipex

all:		${NAME}

clean:
			make fclean -C ./libft	
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
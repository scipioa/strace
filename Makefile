##
## Makefile for strace in /home/bajaze_r/rendu/AUSP_strace
## 
## Made by Ronaël BAJAZET
## Login bajaze_r <bajaze_r@epitech.net>
## 
## Started on  Sun May 17 20:24:39 2015 Ronaël BAJAZET
## Last update Sun May 17 23:29:30 2015 Ronaël BAJAZET
##

CC	=	gcc

RM	=	rm -f

NAME	=	strace

SRC	=	src/main.c \
		src/parse.c \
		src/trace.c \
		src/nbr_arg.c \
		src/tools.c \
		src/tracepid.c \
		src/find.c

OBJ 	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Werror -Wextra
CFLAGS +=	-pedantic -std=c99
CFLAGS +=	-I./header/


all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) $(OBJ) -o $(NAME)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re

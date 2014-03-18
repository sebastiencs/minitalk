##
## Makefile for minitalk in /home/chapui_s/travaux/minitalk/client
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Sun Mar 16 13:56:23 2014 chapui_s
## Last update Sun Mar 16 17:40:28 2014 chapui_s
##

NAME	= client

SRC	= main.c \
	  my_atoi.c \
	  utils.c

OBJ	= $(SRC:.c=.o)

CC	= gcc

RM	= rm -rf

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

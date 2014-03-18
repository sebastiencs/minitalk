##
## Makefile for minitalk in /home/chapui_s/travaux/minitalk/server
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Sun Mar 16 13:56:23 2014 chapui_s
## Last update Mon Mar 17 17:13:55 2014 chapui_s
##

NAME	= server

SRC	= main.c \
	  my_puts.c \
	  my_atoi.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -ggdb

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

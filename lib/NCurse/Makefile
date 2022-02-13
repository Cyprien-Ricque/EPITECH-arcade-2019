##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SRC	=	src/ncurse.cpp	\
		src/color.cpp

OBJ     =	$(SRC:.cpp=.o)

CPPFLAGS    =   -g -W -Wall -Wextra -I include -I ../../core/include -fpic

NAME	=	lib_arcade_ncurses.so

all:	$(NAME)
		mv $(NAME) ..

$(NAME):	$(OBJ)
			g++ -lncursesw -shared -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re:	fclean all
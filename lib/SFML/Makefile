##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SRC	=	src/sfml.cpp

OBJ     =	$(SRC:.cpp=.o)

CPPFLAGS    =    -W -Wall -Wextra -I include -I ../../core/include -fpic

NAME	=	lib_arcade_sfml.so

all:	$(NAME)
		mv $(NAME) ..

$(NAME):	$(OBJ)
		g++ -shared -o $(NAME) $(OBJ) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re:	fclean all

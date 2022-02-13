##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SRC	=	src/opengl.cpp

OBJ     =	$(SRC:.cpp=.o)

CPPFLAGS    =    -W -Wall -Wextra -I include -I ../../core/include -fpic

NAME	=	lib_arcade_opengl.so

all:	$(NAME)
		mv $(NAME) ..

$(NAME):	$(OBJ)
		gcc -shared -o $(NAME) $(OBJ) -L/usr/local/lib -lglut -lGL -lGLU -lGLEW -lopenal -lsndfile

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re:	fclean all
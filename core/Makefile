##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SRC	=	src/main.cpp	\
		src/Arcade.cpp	\
		src/Menu.cpp	\
		src/GameEngine.cpp	\
		src/bitmapReader.cpp	\
		src/Clock.cpp	\
		src/arcadeError.cpp

OBJ     =	$(SRC:.cpp=.o)

CPPFLAGS    =    -W -Wall -Wextra -I include

NAME	=	arcade

all:	$(NAME)
		mv $(NAME) ..

$(NAME):	$(OBJ)
		g++ -o $(NAME) $(OBJ) -ldl

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)


re:	fclean all

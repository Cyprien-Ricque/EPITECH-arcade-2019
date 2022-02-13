##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SRC	=	src/qix.cpp	\
		src/GameEngine.cpp	\
		src/bitmapReader.cpp	\
		src/Fire.cpp	\
		src/GameObject.cpp	\
		src/Map.cpp	\
		src/Player.cpp	\
		src/QixMonster.cpp	\
		src/Sparks.cpp	\
		src/Clock.cpp

OBJ     =	$(SRC:.cpp=.o)

CPPFLAGS    =    -W -Wall -Wextra -I ../../core/include -I include -fpic

NAME	=	lib_arcade_qix.so

all:	$(NAME)
		mv $(NAME) ..

$(NAME):	$(OBJ)
		g++ -shared -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re:	fclean all
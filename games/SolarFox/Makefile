##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##		make clean -C games/SolarFox


SRC	=	src/solarFox.cpp	\
		src/GameEngine.cpp	\
		src/bitmapReader.cpp	\
		src/Clock.cpp	\
		src/Starship.cpp	\
		src/Bullet.cpp	\
		src/Fire.cpp	\
		src/Objective.cpp	\
		src/arcadeError.cpp

OBJ     =	$(SRC:.cpp=.o)

CPPFLAGS    =    -W -Wall -Wextra -I ../../core/include -I include -fpic

NAME	=	lib_arcade_solarfox.so

all:	$(NAME)
		mv $(NAME) ..

$(NAME):	$(OBJ)
		g++ -shared -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f ../$(NAME)

re:	fclean all

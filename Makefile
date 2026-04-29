##
## EPITECH PROJECT, 2026
## Makefile
##

SRC     =   $(shell find src -name "*.c")

OBJ     =   $(SRC:.c=.o)

NAME    =   libcuddle.a

CPPFLAGS =  -I./include

CFLAGS  =   -Wall -Wextra

LDFLAGS =   -L. -lcuddle -lm

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f test_cuddle

re: fclean all

test: all
	gcc main.c -o test_cuddle $(CPPFLAGS) $(CFLAGS) $(LDFLAGS)
	./test_cuddle
SRC = main.c \
      eater.c\
      DoubleLinkedList.c

OBJ = $(SRC:%.c=%.o)

NAME = thr_eat_list
DEBUG_FLAGS = -fsanitize=thread -g

all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

DEBUG: $(OBJ)
	$(CC) $(DEBUG_FLAGS) $(OBJ) -o $(NAME)
	./$(NAME)

DEFAULT: $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
	./$(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

.PHONY: all clean DEBUG DEFAULT
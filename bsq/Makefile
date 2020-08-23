SOURCES = main.c my_readline.c functions.c algo.c
HEADERS = functions.h my_readline.h algo.h
SRCS_PATH = src/
INCLUDES_PATH = includes/
SRCS = $(addprefix $(SRCS_PATH), $(SOURCES))
INCLUDES = $(addprefix $(INCLUDES_PATH), $(HEADERS))
OBJECTS = $(SOURCES:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra
NAME = bsq

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $(NAME) $(OBJECTS)

$(OBJECTS): $(SRCS) $(INCLUDES)
	$(CC) -c $(CFLAGS) $(SRCS) -I$(INCLUDES_PATH)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

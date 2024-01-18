NAME := webserver
CFLAGS := -Wall -Wextra -Werror -std=c++98
CC := g++
SRCS := webserver.cpp Server.cpp socket/ASocket.cpp socket/BindSocket.cpp socket/ListenSocket.cpp
OBJS := $(SRCS:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

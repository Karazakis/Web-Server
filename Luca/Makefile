NAME := webserver

CFLAGS := -Wall -Wextra -Werror -g -std=c++98 

CC := c++

SRCS := webserver.cpp server/AServer.cpp server/WebServer.cpp socket/ASocket.cpp socket/BindSocket.cpp socket/ListenSocket.cpp
OBJS :=  $(SRCS:.cpp=.o)

.cpp.o:
	${CC} ${FLAGS} -c $< -o ${<:.cpp=.o}

RM :=	rm -f

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
NAME := webserver

CFLAGS := -Wall -Wextra -Werror -g -std=c++98 

CC := c++

SRCS := main.cpp \
        Server.cpp WebServer.cpp \
        ConfigParser/Config.cpp ConfigParser/Parser.cpp \
        RequestHandler/RequestHandler.cpp RequestHandler/RequestParser.cpp \
        Socket/ASocket.cpp Socket/BindSocket.cpp Socket/ListenSocket.cpp Socket/SocketUtility.cpp \
		Responder/Responder.cpp

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

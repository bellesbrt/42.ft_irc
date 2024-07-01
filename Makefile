NAME = ircserv

INCLUDES = -I ./includes/
FLAGS = -Wall -Wextra -Werror -std=c++98 -g3

PATH_SRCS = ./srcs/
PATH_COMMANDS = ./srcs/commands/
PATH_CLASSES = ./srcs/classes/
PATH_OBJS = ./objs/

SRCS =	main.cpp

COMMANDS_SRCS =	CAP.cpp \
				PASS.cpp \
				USER.cpp \
				LISTC.cpp \
				NICK.cpp \
				JOIN.cpp \
				PRIVMSG.cpp \
				QUIT.cpp \
				KICK.cpp \
				PART.cpp \
				MODE.cpp \
				TOPIC.cpp \
				WHO.cpp \
				INVITE.cpp

CLASSES_SRCS =	Channel.cpp \
				Commands.cpp \
				CommandArgs.cpp \
				Client.cpp \
				RawMessage.cpp \
				Utils.cpp \
				Server.cpp

OBJS = ${SRCS:%.cpp=$(PATH_OBJS)%.o}
COMMANDS_OBJS = ${COMMANDS_SRCS:%.cpp=$(PATH_OBJS)%.o}
CLASSES_OBJS = ${CLASSES_SRCS:%.cpp=$(PATH_OBJS)%.o}

SERVER_PORT = 4444
SERVER_PASSWORD = 4242

all: $(NAME)
	
run: all
	@./$(NAME) $(SERVER_PORT) $(SERVER_PASSWORD)
	
v: all
	@valgrind --track-fds=yes --quiet ./$(NAME) $(SERVER_PORT) $(SERVER_PASSWORD)

$(NAME): $(OBJS) $(CLASSES_OBJS) $(COMMANDS_OBJS) 
	@clang++ $(FLAGS) $(OBJS) $(CLASSES_OBJS) $(COMMANDS_OBJS) -o $(NAME)

$(PATH_OBJS)%.o: $(PATH_COMMANDS)%.cpp
	@mkdir -p $(PATH_OBJS)
	@clang++ $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo $@ "created"

$(PATH_OBJS)%.o: $(PATH_CLASSES)%.cpp
	@mkdir -p $(PATH_OBJS)
	@clang++ $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo $@ "created"

$(PATH_OBJS)%.o: $(PATH_SRCS)%.cpp
	@mkdir -p $(PATH_OBJS)
	@clang++ $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo $@ "created"

clean:
	@rm -rf $(PATH_OBJS)

fclean: clean
	@rm -rf $(NAME) $(TEST_NAME)

re: fclean all

rerun: re run

.PHONY: all run v clean fclean re rerun

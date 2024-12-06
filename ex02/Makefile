NAME = PmergeMe
SRCS = main.cpp PmergeMe.cpp
OBJS = $(SRCS:.cpp=.o)
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98
DIR = .build
INC = PmergeMe.hpp
OBJS := $(addprefix $(DIR)/, $(OBJS))


all: $(NAME)

$(NAME): $(DIR) $(OBJS)
		$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(DIR)/%.o: %.cpp $(INC)
		$(CC) $(FLAGS) -c $< -o $@

$(DIR):
		mkdir -p $(DIR)

clean:
		rm -fr $(DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re⏎    
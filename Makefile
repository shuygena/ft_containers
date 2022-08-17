NAME = container

SRCS =	main.cpp
INCLUDES =	stack.hpp vector.hpp iterator.hpp random_access_iterator.hpp reverse_iterator.hpp \
			utils.hpp map.hpp rb_tree.hpp node_iterator.hpp

OBJDIR := objs

OBJ = $(SRCS:.cpp=.o)

vpath %.cpp sources
vpath %.hpp headers

CC = c++

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: $(NAME)

%.o: %.cpp $(INCLUDES)
	$(CC) $(FLAGS) -Iheaders -std=c++98 -c $< -o $@
	
$(NAME): $(OBJ) # $(SRCS) $(INCLUDES)
	$(CC) $(FLAGS) $(OBJ) -Iheaders -std=c++98 -o $(NAME)


clean:
	$(RM) $(OBJ)

fclean: clean
			$(RM) $(NAME)

re: fclean all
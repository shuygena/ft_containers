NAME = container

SRCS =	main.cpp
INCLUDES =	stack.hpp vector.hpp iterator.hpp random_access_iterator.hpp reverse_iterator.hpp \
			utils.hpp map.hpp rb_tree.hpp

OBJDIR := objs

OBJ = $(SRCS:.cpp=.o)

vpath %.cpp sources
vpath %.hpp headers

CC = c++

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(addprefix $(OBJDIR)/, $(OBJ)) -Iheaders -std=c++98 -o $(NAME)

%.o: %.cpp | $(OBJDIR) $(INCLUDES)
	$(CC) $(FLAGS) -Iheaders -c $< -o $(OBJDIR)/$@

#$(NAME): $(OBJ) $(INCLUDES)
#			$(CC) $(FLAGS) $(OBJ) -std=c++98 -pedantic -o $(NAME)
#%.o : %.cpp
#			$(CC) $(FLAGS) -c $< -o $@
$(OBJDIR) :
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

#clean:
#			${RM} ${OBJ}

fclean: clean
			$(RM) $(NAME)

re: fclean all
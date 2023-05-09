_END="\033[0m"
_RED="\033[0;31m"
_GREEN="\033[0;32m"
_YELLOW="\033[0;33m"
_CYAN="\033[0;36m"

NAME = PmergeMe

SRC = main.cpp PmergeMe.cpp
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -g3
INC = -Iincludes

SRC_DIR = srcs
OBJ_DIR = objs

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@echo $(_GREEN)Compiling $(OBJ)...$(END)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo $(_CYAN)Compiling $<...$(END)
	@$(CXX) -o $@ -c $< $(CXXFLAGS) $(INC)

clean:
	@echo $(_YELLOW)Cleaning $(OBJ)...$(END)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo $(_RED)Cleaning $(NAME)...$(END)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
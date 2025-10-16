ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


NAME =		libft_malloc_$(HOSTTYPE).so
SL_NAME =	libft_malloc.so
CC =		gcc
CFLAGS = 	-Wall -Wextra -Werror -fPIC

INC_DIR =	includes/
SRC_DIR =	src/
OBJ_DIR =	objs/

SRC_FILES  =   malloc.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
BINS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(BINS)
	$(CC) $(CFLAGS) $(BINS) -shared -o $(NAME) -lpthread
	ln -fs ${NAME} ${SL_NAME}

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)/malloc.h Makefile
	$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

$(OBJ_DIR):
	mkdir -p objs

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(SL_NAME)

re: fclean all

.PHONY: all re run clean fclean
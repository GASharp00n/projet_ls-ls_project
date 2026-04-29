CC = clang

NAME = ls

CFLAGS = -Wall -Wextra -Werror -Iinclude

SRCS = src/display_dir.c \
       src/file_loader.c \
       src/l_option.c \
       src/path_handler.c \
       src/print_file.c \
       src/sort_files.c \
       src/str_functions.c \
	   src/h_option.c

MAIN = src/main.c

TEST = test/test_directory.c \
    test/test_flags.c \
    test/test_l_option.c \
    test/test_load_files.c \
    test/test_sort.c \
    test/test_utils.c \
	test/test_h.c

OBJS = $(SRCS:.c=.o)
OBJ_MAIN = $(MAIN:.c=.o)
OBJS_TEST = $(TEST:.c=.o)

TEST_FLAGS = -lcriterion

.PHONY: all clean fclean re tests

all: $(NAME)

$(NAME): $(OBJS) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJS) $(OBJ_MAIN) -o $(NAME)

ut.out: $(OBJS) $(OBJS_TEST)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_TEST) $(TEST_FLAGS) -o ut.out

tests: ut.out
	./ut.out

clean:
	rm -f $(OBJS) $(OBJ_MAIN) $(OBJS_TEST)

fclean: clean
	rm -f $(NAME) ut.out

re: fclean all

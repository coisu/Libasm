NAME         = libasm.a

CC           = nasm
CCFLAGS      = -f elf64
SRC_DIR      = srcs
BONUS_DIR    = bonus_srcs
OBJ_DIR      = objs
MANUAL_SRCS  = manual_srcs
MANUAL_TESTS = manual_tests

SRC          = $(addprefix $(SRC_DIR)/, ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s)
BONUS_SRC    = $(addprefix $(BONUS_DIR)/, ft_strlen_bonus.s ft_strcpy_bonus.s ft_strcmp_bonus.s ft_write_bonus.s ft_read_bonus.s ft_strdup_bonus.s)
OBJ          = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.s=.o)))
BONUS_OBJ    = $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_SRC:.s=.o)))
MAIN         = main.c
TEST_BIN     = test_libasm


# Default target
all: $(NAME)

# Create the library from object files
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

# Compile .s files into .o files in the obj directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.s
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -o $@ $<

# Bonus target
bonus: $(BONUS_OBJ)
	ar rcs $(NAME) $(BONUS_OBJ)

# Clean object files and test binary
clean:
	rm -rf $(OBJ_DIR) $(MANUAL_TESTS)

# Full clean
fclean: clean
	rm -f $(NAME) $(TEST_BIN)

# Rebuild everything
re: fclean all

# Test the library with the main file (automatic testing)
test: $(NAME)
	gcc -Wall -Wextra -Werror $(MAIN) $(NAME) -o $(TEST_BIN)
	./$(TEST_BIN)

# Manual testing
manual: prepare_objs $(SRC)
	@mkdir -p $(MANUAL_TESTS)
	@for src in $(SRC); do \
		obj_file=$$(basename $$src .s); \
		nasm -f elf64 $$src -o $(OBJ_DIR)/$$obj_file.o; \
		gcc -Wall -Wextra -Werror $(MANUAL_SRCS)/$$obj_file.c $(OBJ_DIR)/$$obj_file.o -o $(MANUAL_TESTS)/$$obj_file; \
	done
	@echo "Manual testing binaries are located in the $(MANUAL_TESTS) directory."

# Ensure objs directory is created
prepare_objs:
	@mkdir -p $(OBJ_DIR)

.PHONY: all clean fclean re bonus test manual prepare_objs

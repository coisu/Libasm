NAME         = libasm.a

# Compiler and Tools
CC           = gcc
NASM         = nasm
AR           = ar
CFLAGS       = -Wall -Wextra -Werror -fPIE
NASMFLAGS    = -f elf64
LDFLAGS      = -pie

# Directories
SRC_DIR      = srcs
BONUS_DIR    = bonus_srcs
OBJ_DIR      = objs
MANUAL_SRCS  = manual_srcs
MANUAL_TESTS = manual_tests

# Source and Object Files
SRC          = $(addprefix $(SRC_DIR)/, ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s)
BONUS_SRC    = $(addprefix $(BONUS_DIR)/, ft_strlen_bonus.s ft_strcpy_bonus.s ft_strcmp_bonus.s ft_write_bonus.s ft_read_bonus.s ft_strdup_bonus.s)
OBJ          = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.s=.o)))
BONUS_OBJ    = $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_SRC:.s=.o)))
MAIN         = main.c
TEST_BIN     = test_libasm

# Default target
all: $(NAME)

# Create the library from object files
$(NAME): $(OBJ)
	$(AR) rcs $(NAME) $(OBJ)

# Compile .s files into .o files in the obj directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(OBJ_DIR)
	$(NASM) $(NASMFLAGS) -o $@ $<

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.s
	@mkdir -p $(OBJ_DIR)
	$(NASM) $(NASMFLAGS) -o $@ $<

# Bonus target
bonus: $(BONUS_OBJ)
	$(AR) rcs $(NAME) $(BONUS_OBJ)

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
	$(CC) $(CFLAGS) $(MAIN) $(NAME) -o $(TEST_BIN) $(LDFLAGS)
	./$(TEST_BIN)

# Manual testing (STDIN-based mode)
manual: prepare_objs $(SRC)
	@mkdir -p $(MANUAL_TESTS)
	@for src in $(SRC); do \
		obj_file=$$(basename $$src .s); \
		$(NASM) $(NASMFLAGS) $$src -o $(OBJ_DIR)/$$obj_file.o; \
		$(CC) $(CFLAGS) $(MANUAL_SRCS)/$$obj_file.c $(OBJ_DIR)/$$obj_file.o -o $(MANUAL_TESTS)/$$obj_file $(LDFLAGS); \
	done
	@echo "Manual testing binaries are located in the $(MANUAL_TESTS) directory."
	@echo "Run individual binaries in $(MANUAL_TESTS) to manually test with STDIN."

# Ensure objs directory is created
prepare_objs:
	@mkdir -p $(OBJ_DIR)

.PHONY: all clean fclean re bonus test manual prepare_objs

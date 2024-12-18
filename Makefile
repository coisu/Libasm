# Compiler and Tools
CC           = gcc
NASM         = nasm
CFLAGS       = -Wall -Wextra -Werror
NASMFLAGS    = -f elf64

# Directories
SRC_DIR      = srcs
OBJ_DIR      = objs
MANUAL_SRCS  = manual_srcs
MANUAL_TESTS = manual_tests

# Source and Object Files
SRC          = $(addprefix $(SRC_DIR)/, ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s)
OBJ          = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.s=.o)))
MAIN         = main.c
TEST_BIN     = test_libasm

# Default target
all: $(TEST_BIN)

# Create the test binary
$(TEST_BIN): $(OBJ) $(MAIN)
	$(CC) $(CFLAGS) $(OBJ) $(MAIN) -o $(TEST_BIN) -no-pie

# Compile .s files into .o files in the obj directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(OBJ_DIR)
	$(NASM) $(NASMFLAGS) -o $@ $<

# Test the library with the main file (automatic testing)
test: $(TEST_BIN)
	./$(TEST_BIN)

# Manual testing (STDIN-based mode)
manual: prepare_objs $(SRC)
	@mkdir -p $(MANUAL_TESTS)
	@for src in $(SRC); do \
		obj_file=$$(basename $$src .s); \
		$(NASM) $(NASMFLAGS) $$src -o $(OBJ_DIR)/$$obj_file.o; \
		$(CC) $(CFLAGS) manual_srcs/manual_tests.h $(MANUAL_SRCS)/$$obj_file.c $(OBJ_DIR)/*.o -o $(MANUAL_TESTS)/$$obj_file -no-pie; \
	done
	@echo "Manual testing binaries are located in the $(MANUAL_TESTS) directory."
	@echo "Run individual binaries in $(MANUAL_TESTS) to manually test with STDIN."

# Clean object files and test binary
clean:
	rm -rf $(OBJ_DIR) $(MANUAL_TESTS)

fclean: clean
	rm -f $(TEST_BIN)

# Rebuild everything
re: fclean all

# Ensure objs directory is created
prepare_objs:
	@mkdir -p $(OBJ_DIR)

.PHONY: all clean fclean re test manual

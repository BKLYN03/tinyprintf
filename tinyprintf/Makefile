# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla

# Paths
SRC = src/tinyprintf.c
TEST = tests/test_tinyprintf.c
OBJ = $(SRC:.c=.o)

# Targets
all: $(OBJ)

# Create the object file
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Run tests
check: $(OBJ)
	$(CC) $(CFLAGS) --coverage -fPIC -o test $(TEST) $(OBJ) -lcriterion -lgcov
	./test

# Clean up
clean:
	rm -f $(OBJ) test *.gcda *.gcno *.gcov

# Build coverage report
coverage: check
	gcovr --html --html-nested --output=report.html
	firefox report.html

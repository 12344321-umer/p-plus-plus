 
# P++ Compiler Makefile (Windows)


# Tools — adjust paths if win_flex/win_bison
# are not in the same folder as your sources
FLEX    = win_flex
BISON   = win_bison
CC      = gcc
TARGET  = p-plus-plus.exe

# All C sources that gcc will compile
SRCS    = lex.yy.c parser.tab.c ast.c semantic.c main.c


# Default target — build everything

all: $(TARGET)

# Step 1: run bison on parser.y
# generates parser.tab.c and parser.tab.h
parser.tab.c parser.tab.h: parser.y
	$(BISON) -d parser.y

# Step 2: run flex on scanner.l
# generates lex.yy.c
# depends on parser.tab.h so tokens are defined first
lex.yy.c: scanner.l parser.tab.h
	$(FLEX) scanner.l

# Step 3: compile everything into one executable
$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS)


# Clean generated files

clean:
	del /Q lex.yy.c parser.tab.c parser.tab.h $(TARGET) 2>nul || true

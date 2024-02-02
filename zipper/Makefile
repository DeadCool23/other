CC = g++

VALGRIND = valgrind --leak-check=full --quiet
CPPFLAGS = -Wall -Werror -Wpedantic -Wextra -Wvla -Wfloat-equal -Wfloat-conversion
INC = -I inc -I classes
DYNLIBS = 

TARGET = nzipper

SRCDIR = src
SRC = $(wildcard $(SRCDIR)/*.cpp)

OBJDIR = ./out
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

.PHONY: build
build: $(TARGET)

.PHONY: clean
clean:
	$(RM) $(TARGET) -r $(OBJDIR)

.PHONY: debug
debug: CPPFLAGS += -O0
debug: CPPFLAGS += -DDBG_PRINT
debug: $(TARGET)

.PHONY: release
release: CPPFLAGS += -O3
release: $(TARGET)

$(TARGET): $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) -o $@ $(CPPFLAGS) $(DYNLIBS) $(INC)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CC) -c $< -o $@ $(CPPFLAGS) $(DYNLIBS) $(INC)

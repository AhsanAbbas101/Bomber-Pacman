CC = g++
CFLAGS = -w -g3 -Wall -fmessage-length=0 -Iinclude #-Werror
LDFLAGS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lglut -lGLU -lGL -lX11 -lfreeimage -pthread 
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
EXE = $(BIN_DIR)/game
SETUP = sudo apt-get install freeglut3-dev glew-utils libglew-dev libfreeimage-dev	

# Find all source files recursively
SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Create the build directory and its subdirectories
$(shell mkdir -p $(dir $(OBJS)))

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJS) | $(BIN_DIR) 
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@


clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(BIN_DIR)

play:
	$(EXE)

install:
	$(SETUP)
	
-include $(DEPS)



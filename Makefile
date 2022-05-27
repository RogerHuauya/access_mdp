CC := g++
SRC_DIR := src
TEST_DIR := test
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
HDR := $(wildcard include/*.hpp)

TARGET := main

CPPFLAGS := 
CFLAGS   := -Wall
LDFLAGS  := 
LDLIBS   := 
INC := -I include
PCFG =  -lzbar -lwiringPi -lpthread `pkg-config --cflags --libs opencv`

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ) | $(BUILD_DIR)
	@echo Linking objects
	$(CC) $(TEST_DIR)/$(TARGET).cpp $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $(BUILD_DIR)/$@ $(PCFG) $(INC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo Creating object file $@
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ $(PCFG) $(INC)

$(BUILD_DIR) $(OBJ_DIR):
	@echo Creating build folder
	mkdir -p $@

clean:
	@$(RM) -rv $(BUILD_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)


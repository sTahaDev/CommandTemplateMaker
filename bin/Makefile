APP_NAME = Ctm
MAIN_FILE = main.cpp

SRC_DIR = ../src
INCLUDE_DIR = ../include
LIB_DIR = ../lib 

FLAGS = -std=c++17

CPP_FILES = $(INCLUDE_DIR)/CTM/ctm.cpp

all:
	g++ $(SRC_DIR)/$(MAIN_FILE) $(CPP_FILES) $(FLAGS) -I$(INCLUDE_DIR) -L$(LIB_DIR) -o ./$(APP_NAME)
	./$(APP_NAME) new -make
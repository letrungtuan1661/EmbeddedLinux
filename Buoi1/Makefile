CUR_DIR = .
BIN_DIR = $(CUR_DIR)/bin
INC_DIR = $(CUR_DIR)/inc
SRC_DIR = $(CUR_DIR)/src
OBJ_DIR = $(CUR_DIR)/obj
LIB_DIR = $(CUR_DIR)/lib
LIB_STATIC_DIR = $(LIB_DIR)/static
LIB_SHARED_DIR = $(LIB_DIR)/shared

STATIC_LIB_NAME = static
DYNAMIC_LIB_NAME = dynamic
.PHONY: all create_obj create_lib linking execute clean

export LD_LIBRARY_PATH=$(LIB_SHARED_DIR):$LD_LIBRARY_PATH

all: create_obj create_lib linking execute

create_obj:
	@gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o -I $(INC_DIR)
	@gcc -c -fPIC $(SRC_DIR)/staticlib.c  -o $(OBJ_DIR)/staticlib.o  -I $(INC_DIR)
	@gcc -c -fPIC $(SRC_DIR)/dynamiclib.c -o $(OBJ_DIR)/dynamiclib.o -I $(INC_DIR)  

create_lib:
	@ar rcs $(LIB_STATIC_DIR)/lib$(STATIC_LIB_NAME).a $(OBJ_DIR)/staticlib.o 
	@gcc -shared -o $(LIB_SHARED_DIR)/lib$(DYNAMIC_LIB_NAME).so $(OBJ_DIR)/dynamiclib.o

linking:
	@gcc -o $(BIN_DIR)/program $(OBJ_DIR)/main.o -L$(LIB_STATIC_DIR) -l$(STATIC_LIB_NAME) -L$(LIB_SHARED_DIR) -l$(DYNAMIC_LIB_NAME)

execute:
	@$(BIN_DIR)/program

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(BIN_DIR)/*
	rm -rf $(LIB_STATIC_DIR)/* $(LIB_SHARED_DIR)/*
	rm -f $(BIN_DIR)/program


SRC_DIR = ../src
BUILD_DIR = build
BIN_DIR = bin
PROJECT_NAME = ReadySpice
TARGET_NAME = readyspice
SETUP_NAME = $(BIN_DIR)/$(TARGET_NAME)

all: clean_exe cmake compile run

cmake:
	@echo
	@cmake -B $(BUILD_DIR) -S $(SRC_DIR)
compile:
	@echo
	@make -C $(BUILD_DIR)
clean_exe:
	@echo
	@rm -rf $(BIN_DIR)/*
clean: clean_exe
	@echo
	@make -C $(BUILD_DIR) clean
clean_all:
	@echo
	@rm -rf $(BIN_DIR)/*
	@rm -rf $(BUILD_DIR)/*
run:
	@echo
	@./envs.sh && $(SETUP_NAME) $(ARGS)

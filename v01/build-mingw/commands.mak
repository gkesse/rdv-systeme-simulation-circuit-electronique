SRC_DIR = ../src
BUILD_DIR = build
BIN_DIR = bin
PROJECT_NAME = ReadySpice
TARGET_NAME = readyspice
SETUP_NAME = $(BIN_DIR)\$(TARGET_NAME)

all: clean_exe cmake compile run

cmake:
	@echo.
	@cmake -B $(BUILD_DIR) -S $(SRC_DIR) \
	-G "MinGW Makefiles" \
	-D CMAKE_PREFIX_PATH="C:\Qt\6.5.2\mingw_64\lib\cmake"
compile:
	@echo.
	@make -C $(BUILD_DIR)
clean_exe:
	@echo.
	@del /s /q $(BIN_DIR)\*
clean: clean_exe
	@echo.
	@make -C $(BUILD_DIR) clean
clean_all:
	@echo.
	@rd /q /s $(BUILD_DIR)
run:
	@echo.
	@envs && $(SETUP_NAME) $(ARGS)

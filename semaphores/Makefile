JFLAGS = -g  # debug info
SRC_DIR = . # source directory
BIN_DIR = bin # destination folder for .class files
SRCS = $(wildcard $(SRC_DIR)/*.java) # all .java files in the source directory
CLASSES = $(patsubst $(SRC_DIR)/%.java,$(BIN_DIR)/%.class,$(SRCS)) # corresponding .class files

.PHONY: all build run clean 

all: build

build: $(BIN_DIR) $(CLASSES)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(BIN_DIR)/%.class: $(SRC_DIR)/%.java
	@echo Compiling $<
	@javac -d $(BIN_DIR) $(JFLAGS) $<

run: build
	@echo Running Main
	@java -cp $(BIN_DIR) Main

clean:
	@echo Cleaning
	@if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)
